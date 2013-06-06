/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    Mark Page
*/

#include "Network/precomp.h"
#include "API/Network/NetGame/connection.h"
#include "API/Network/NetGame/connection_site.h"
#include "API/Core/System/databuffer.h"
#include "network_event.h"
#include "network_data.h"
#include "connection_impl.h"

CL_NetGameConnection_Impl::CL_NetGameConnection_Impl()
{
}

void CL_NetGameConnection_Impl::start(CL_NetGameConnection *xbase, CL_NetGameConnectionSite *xsite, const CL_TCPConnection &xconnection)
{
	base = xbase;
	site = xsite;
	connection = xconnection;
	socket_name = connection.get_remote_name();
	is_connected = true;
	thread.start(this, &CL_NetGameConnection_Impl::connection_main);
}

void CL_NetGameConnection_Impl::start(CL_NetGameConnection *xbase, CL_NetGameConnectionSite *xsite, const CL_SocketName &xsocket_name)
{
	base = xbase;
	site = xsite;
	socket_name = xsocket_name;
	is_connected = false;
	thread.start(this, &CL_NetGameConnection_Impl::connection_main);
}

CL_NetGameConnection_Impl::~CL_NetGameConnection_Impl()
{
	stop_event.set();
	thread.join();
}

void CL_NetGameConnection_Impl::set_data(const CL_StringRef &name, void *new_data)
{
	for (std::vector<AttachedData>::iterator it = data.begin(); it != data.end(); ++it)
	{
		if (it->name == name)
		{
			it->data = new_data;
			return;
		}
	}
	AttachedData d;
	d.name = name;
	d.data = new_data;
	data.push_back(d);
}

void *CL_NetGameConnection_Impl::get_data(const CL_StringRef &name) const
{
	for (std::vector<AttachedData>::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		if (it->name == name)
			return it->data;
	}
	return 0;
}

void CL_NetGameConnection_Impl::send_event(const CL_NetGameEvent &game_event)
{
	CL_MutexSection mutex_lock(&mutex);
	Message message;
	message.type = Message::type_message;
	message.event = game_event;
	send_queue.push_back(message);
	queue_event.set();
}

void CL_NetGameConnection_Impl::disconnect()
{
	CL_MutexSection mutex_lock(&mutex);
	Message message;
	message.type = Message::type_disconnect;
	send_queue.push_back(message);
	queue_event.set();
}

CL_SocketName CL_NetGameConnection_Impl::get_remote_name() const
{
	return socket_name;
}

void CL_NetGameConnection_Impl::connection_main()
{
	try
	{
		if (!is_connected)
			connection = CL_TCPConnection(socket_name);
		is_connected = true;
		site->add_network_event(CL_NetGameNetworkEvent(base, CL_NetGameNetworkEvent::client_connected));

		int bytes_received = 0;
		int bytes_sent = 0;
		const int max_event_packet_size = 32000 + 2;
		CL_DataBuffer receive_buffer(max_event_packet_size);
		CL_DataBuffer send_buffer;

		bool send_graceful_close = false;

		connection.set_nodelay(true);
		while (true)
		{
			bool send_buffer_empty = (bytes_sent == send_buffer.get_size());

			CL_Event read_event = connection.get_read_event();
			CL_Event send_event = send_buffer_empty ? queue_event : connection.get_write_event();
			int wakeup_reason = CL_Event::wait(stop_event, read_event, send_event);
			if (wakeup_reason <= 0)
			{
				break;
			}
			else if (wakeup_reason == 1) // we got data to receive
			{
				int bytes = connection.read(receive_buffer.get_data() + bytes_received, receive_buffer.get_size() - bytes_received, false);
				if (bytes <= 0)
				{
					connection.disconnect_graceful();
					break;
				}

				bytes_received += bytes;

				int bytes_consumed = 0;
				bool exit = read_data(receive_buffer.get_data(), bytes_received, bytes_consumed);

				if (bytes_consumed >= 0)
				{
					memmove(receive_buffer.get_data(), receive_buffer.get_data() + bytes_consumed, bytes_received - bytes_consumed);
					bytes_received -= bytes_consumed;
				}

				if (exit)
					break;
			}
			else if (wakeup_reason == 2) // we got data to send
			{
				if (!send_buffer_empty)
				{
					int bytes = connection.write(send_buffer.get_data() + bytes_sent, send_buffer.get_size() - bytes_sent, false);
					if (bytes < 0)
						throw Exception("TCPConnection.write failed");
					bytes_sent += bytes;
				}

				if (bytes_sent == send_buffer.get_size())
				{
					if (send_graceful_close)
					{
						connection.disconnect_graceful();
						break;
					}
					else
					{
						bytes_sent = 0;
						send_buffer.set_size(0);
						send_graceful_close = write_data(send_buffer);
					}
				}
			}
		}

		site->add_network_event(CL_NetGameNetworkEvent(base, CL_NetGameNetworkEvent::client_disconnected));
	}
	catch (const Exception& e)
	{
		site->add_network_event(CL_NetGameNetworkEvent(base, CL_NetGameNetworkEvent::client_disconnected, CL_NetGameEvent(e.message)));
	}
}

bool CL_NetGameConnection_Impl::read_data(const void *data, int size, int &bytes_consumed)
{
	bytes_consumed = 0;
	while (bytes_consumed != size)
	{
		int bytes = 0;
		CL_NetGameEvent incoming_event = CL_NetGameNetworkData::receive_data(static_cast<const char*>(data) + bytes_consumed, size - bytes_consumed, bytes);
		bytes_consumed += bytes;

		if (bytes == 0)
		{
			return false;
		}
		else if (incoming_event.get_name() == "_close")
		{
			return true;
		}

		site->add_network_event(CL_NetGameNetworkEvent(base, incoming_event));
	}
	return false;
}

bool CL_NetGameConnection_Impl::write_data(CL_DataBuffer &buffer)
{
	CL_MutexSection mutex_lock(&mutex);
	queue_event.reset();
	std::vector<Message> new_send_queue;
	send_queue.swap(new_send_queue);
	mutex_lock.unlock();
	for (unsigned int i = 0; i < new_send_queue.size(); i++)
	{
		if (new_send_queue[i].type == Message::type_message)
		{
			CL_DataBuffer packet = CL_NetGameNetworkData::send_data(new_send_queue[i].event);

			int pos = buffer.get_size();
			buffer.set_size(pos + packet.get_size());
			memcpy(buffer.get_data() + pos, packet.get_data(), packet.get_size());
		}
		else if (new_send_queue[i].type == Message::type_disconnect)
		{
			return true;
		}
	}
	return false;
}

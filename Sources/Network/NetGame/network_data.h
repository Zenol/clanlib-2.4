/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
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
*/

#pragma once

#include "API/Core/System/databuffer.h"
#include "API/Network/NetGame/event.h"
#include "API/Network/Socket/tcp_connection.h"

class CL_DomDocument;
class CL_DomElement;

class CL_NetGameNetworkData
{
public:
	static CL_NetGameEvent receive_data(CL_TCPConnection connection);
	static void send_data(CL_TCPConnection connection, const CL_NetGameEvent &e);

private:
	static CL_NetGameEvent decode_event(const CL_DataBuffer &data);
	static CL_DataBuffer encode_event(const CL_NetGameEvent &e);

	static unsigned int get_encoded_length(const CL_NetGameEventValue &value);
	static unsigned int encode_value(unsigned char *d, const CL_NetGameEventValue &value);

	static CL_NetGameEventValue decode_value(unsigned char type, const unsigned char *d, unsigned int length, unsigned int &pos);

	enum { packet_limit = 32000 };
};

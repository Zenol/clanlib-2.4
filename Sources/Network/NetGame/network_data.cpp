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

#include "Network/precomp.h"
#include "API/Core/System/databuffer.h"
#include "API/Core/IOData/iodevice_memory.h"
#include "API/Core/XML/dom_document.h"
#include "API/Core/XML/dom_element.h"
#include "API/Core/XML/dom_text.h"
#include "API/Core/Text/string_help.h"
#include "network_data.h"

CL_NetGameEvent CL_NetGameNetworkData::receive_data(CL_TCPConnection connection)
{
	int size = connection.read_uint16();
	if (size > packet_limit)
		throw CL_Exception("Incoming message too big");
	CL_DataBuffer buffer(size);
	connection.read(buffer.get_data(), buffer.get_size());
	return decode_event(buffer);
}

void CL_NetGameNetworkData::send_data(CL_TCPConnection connection, const CL_NetGameEvent &e)
{
	CL_DataBuffer buffer = encode_event(e);
	if (buffer.get_size() > packet_limit)
		throw CL_Exception("Outgoing message too big");
	connection.write_uint16(buffer.get_size());
	connection.write(buffer.get_data(), buffer.get_size());
}

CL_NetGameEvent CL_NetGameNetworkData::decode_event(const CL_DataBuffer &data)
{
	const unsigned char *d = data.get_data<unsigned char>();
	unsigned int length = data.get_size();
	if (length < 3)
		throw CL_Exception("Invalid network data");

	unsigned int name_length = *reinterpret_cast<const unsigned short*>(d);
	if (length < 2 + name_length + 1)
		throw CL_Exception("Invalid network data");
	std::string name = std::string(reinterpret_cast<const char*>(d + 2), name_length);

	CL_NetGameEvent e(name);
	unsigned int pos = 2 + name_length;
	while (true)
	{
		if (pos >= length)
			throw CL_Exception("Invalid network data");
		unsigned char type = d[pos++];
		if (type == 0)
			break;
		e.add_argument(decode_value(type, d, length, pos));
	}
	return e;
}

CL_NetGameEventValue CL_NetGameNetworkData::decode_value(unsigned char type, const unsigned char *d, unsigned int length, unsigned int &pos)
{
	switch (type)
	{
	case 1: // null
		return CL_NetGameEventValue(CL_NetGameEventValue::null);
	case 2: // uint
	{
			if (pos + 4 > length)
				throw CL_Exception("Invalid network data");
			unsigned int v = *reinterpret_cast<const unsigned int*>(d + pos);
			pos += 4;
			return CL_NetGameEventValue(v);
		}
	case 3: // int
		{
			if (pos + 4 > length)
				throw CL_Exception("Invalid network data");
			int v = *reinterpret_cast<const int*>(d + pos);
			pos += 4;
			return CL_NetGameEventValue(v);
		}
	case 4: // number
		{
			if (pos + 4 > length)
				throw CL_Exception("Invalid network data");
			float v = *reinterpret_cast<const float*>(d + pos);
			pos += 4;
			return CL_NetGameEventValue(v);
		}
	case 5: // false boolean
		return CL_NetGameEventValue(false);
	case 6: // true boolean
		return CL_NetGameEventValue(true);
	case 7: // string
		{
			if (pos + 2 > length)
				throw CL_Exception("Invalid network data");
			unsigned short name_length = *reinterpret_cast<const unsigned short*>(d + pos);
			pos += 2;
			if (pos + name_length > length)
				throw CL_Exception("Invalid network data");
			CL_String value(reinterpret_cast<const char*>(d + pos), name_length);
			pos += name_length;
			return CL_NetGameEventValue(value);
	}
	case 8: // complex
	{
		CL_NetGameEventValue value(CL_NetGameEventValue::complex);
			while (true)
		{
				if (pos >= length)
					throw CL_Exception("Invalid network data");
				unsigned char type = d[pos++];
				if (type == 0)
					break;
				value.add_member(decode_value(type, d, length, pos));
		}
		return value;
	}
	case 9: // uchar
	{
			if (pos + 1 > length)
				throw CL_Exception("Invalid network data");
			unsigned char v = *reinterpret_cast<const unsigned char*>(d + pos);
			pos += 1;
			return CL_NetGameEventValue(v);
		}
	case 10: // char
		{
			if (pos + 1 > length)
				throw CL_Exception("Invalid network data");
			char v = *reinterpret_cast<const char*>(d + pos);
			pos += 1;
			return CL_NetGameEventValue(v);
		}
	default:
		throw CL_Exception("Invalid network data");
	}
}

CL_DataBuffer CL_NetGameNetworkData::encode_event(const CL_NetGameEvent &e)
{
	unsigned int length = 3 + e.get_name().length();
	for (unsigned int i = 0; i < e.get_argument_count(); i++)
		length += get_encoded_length(e.get_argument(i));

	CL_DataBuffer data(length);
	unsigned char *d = data.get_data<unsigned char>();

	// Write name (2 + name length)
	unsigned int name_length = e.get_name().length();
	*reinterpret_cast<unsigned short*>(d) = name_length;
	d += 2;
	memcpy(d, e.get_name().data(), name_length);
	d += name_length;

	for (unsigned int i = 0; i < e.get_argument_count(); i++)
		d += encode_value(d, e.get_argument(i));

	// Write end marker
	*d = 0;

	return data;
}

unsigned int CL_NetGameNetworkData::encode_value(unsigned char *d, const CL_NetGameEventValue &value)
{
	switch (value.get_type())
	{
	case CL_NetGameEventValue::null:
		*d = 1;
		return 1;
	case CL_NetGameEventValue::uinteger:
		*d = 2;
		*reinterpret_cast<unsigned int*>(d + 1) = value.to_uinteger();
		return 5;
	case CL_NetGameEventValue::integer:
		*d = 3;
		*reinterpret_cast<int*>(d + 1) = value.to_integer();
		return 5;
	case CL_NetGameEventValue::number:
		*d = 4;
		*reinterpret_cast<float*>(d + 1) = value.to_number();
		return 5;
	case CL_NetGameEventValue::boolean:
		*d = value.to_boolean() ? 6 : 5;
		return 1;
	case CL_NetGameEventValue::string:
		{
			std::string s = value.to_string();
			*d = 7;
			*reinterpret_cast<unsigned short*>(d + 1) = s.length();
			memcpy(d + 3, s.data(), s.length());
			return 3 + s.length();
		}
	case CL_NetGameEventValue::complex:
		{
			d[0] = 8;
			unsigned l = 1;
			for (unsigned int i = 0; i < value.get_member_count(); i++)
				l += encode_value(d + l, value.get_member(i));
			d[l] = 0;
			l++;
			return l;
		}
	case CL_NetGameEventValue::ucharacter:
		*d = 9;
		*reinterpret_cast<unsigned char*>(d + 1) = value.to_ucharacter();
		return 2;
	case CL_NetGameEventValue::character:
		*d = 10;
		*reinterpret_cast<char*>(d + 1) = value.to_character();
		return 2;
	default:
		throw CL_Exception("Unknown game event value type");
	}
}

unsigned int CL_NetGameNetworkData::get_encoded_length(const CL_NetGameEventValue &value)
{
	switch (value.get_type())
	{
	case CL_NetGameEventValue::null:
	case CL_NetGameEventValue::boolean:
		return 1;
	case CL_NetGameEventValue::character:
	case CL_NetGameEventValue::ucharacter:
		return 2;
	case CL_NetGameEventValue::uinteger:
	case CL_NetGameEventValue::integer:
	case CL_NetGameEventValue::number:
		return 5;
	case CL_NetGameEventValue::string:
		return 1 + 2 + value.to_string().length();
	case CL_NetGameEventValue::complex:
		{
			unsigned l = 2;
			for (unsigned int i = 0; i < value.get_member_count(); i++)
				l += get_encoded_length(value.get_member(i));
			return l;
		}
	default:
		throw CL_Exception("Unknown game event value type");
	}
}

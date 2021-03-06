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

/// \addtogroup clanNetwork_Socket clanNetwork Socket
/// \{

#pragma once

#include "../api_network.h"
#include "../../Core/System/sharedptr.h"

class CL_SocketName_Impl;

/// \brief Socket name; container class for an IP address and port.
///
/// \xmlonly !group=Network/Sockets! !header=network.h! \endxmlonly
class CL_API_NETWORK CL_SocketName
{
/// \name Construction
/// \{

public:
	/// \brief Constructs a new socket name.
	/** <p>If no address is specified, the socket address will default to INADDR_ANY.
	    If no port is specified, it will default to port 0.</p>*/
	CL_SocketName();

	/// \brief Constructs a SocketName
	///
	/// \param port = String
	CL_SocketName(const CL_String &port);

	/// \brief Constructs a SocketName
	///
	/// \param address = String
	/// \param port = String
	CL_SocketName(const CL_String &address, const CL_String &port);

/// \}
/// \name Attributes
/// \{

public:
	/// \brief Returns the address part of the socket name.
	CL_String get_address() const;

	/// \brief Returns the port part of the socket name.
	CL_String get_port() const;

	/// \brief Returns true if objects are the same.
	bool operator == (const CL_SocketName &other_instance) const;

	/// \brief Returns true if the other address is less.
	/** <p>This is used for sorting
	    purposes (eg. if you use a std::map<CL_SocketName, CL_Socket>), and sorts
	    the address based on lowest IP number address.</p>*/
	bool operator < (const CL_SocketName &other_instance) const;

	/// \brief Returns true if the other address is greater.
	/** <p>This is used for sorting
	    purposes (eg. if you use a std::map<CL_SocketName, CL_Socket>), and sorts
	    the address based on lowest IP number address.</p>*/
	bool operator > (const CL_SocketName &other_instance) const;

/// \}
/// \name Operations
/// \{

public:
	/// \brief Set the socket name using a hostname and port.
	///
	/// \param hostname Can be an IPv4 dotted-quad, hostname or a valid IPv6 address.
	/// \param port Port number.
	void set_name(const CL_String &hostname, const CL_String &port);

	/// \brief Set the IP address.
	void set_address(const CL_String &address);

	/// \brief Set the IP port.
	void set_port(const CL_String &port);

	/// \brief Perform a DNS lookup, if needed, for the IP v4 address.
	CL_String lookup_ipv4() const;

	/// \brief Perform a DNS lookup, if needed, for the hostname.
	CL_String lookup_hostname() const;

	/// \brief Create socket name that uses the IP v4 address as its address.
	CL_SocketName to_ipv4();

	/// \brief Create socket name that uses the hostname as its address.
	CL_SocketName to_hostname();

	/// \brief Fill the socket name into a C sockets sockaddr structure.
	void to_sockaddr(int domain, struct sockaddr *addr, int len) const;

	/// \brief Get the socket name from a C sockets sockaddr structure.
	void from_sockaddr(int domain, struct sockaddr *addr, int len);

/// \}
/// \name Implementation
/// \{

private:
	CL_SharedPtr<CL_SocketName_Impl> impl;
/// \}
};

/// \}

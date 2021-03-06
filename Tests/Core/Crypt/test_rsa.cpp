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
**    Mark Page
**    (if your name is missing here, please add it)
*/

#include "test.h"

class Crypt_Server
{
public:
	Crypt_Server(TestApp *testapp) : m_pTestApp(testapp)
	{
	}

	void create_keypair()
	{
		CL_RSA::create_keypair(m_Random, m_private_exponent, m_public_exponent, m_modulus);
	}

	void create_crypt_key()
	{
		m_CryptKey = CL_Secret(16);
		m_Random.get_random_bytes(m_CryptKey.get_data(), m_CryptKey.get_size());
		m_WrappedCryptKey = CL_RSA::encrypt(2, m_Random, m_public_exponent, m_modulus, m_CryptKey);

	}

	CL_DataBuffer export_wrap_crypt_key(const CL_DataBuffer &client_public_exponent, const CL_DataBuffer &client_public_modulus)
	{
		return CL_RSA::encrypt(2, m_Random, client_public_exponent, client_public_modulus, m_CryptKey);
	}

	TestApp *m_pTestApp;
	CL_Random m_Random;
	CL_Secret m_CryptKey;
	CL_DataBuffer m_WrappedCryptKey;

	CL_Secret m_private_exponent;
	CL_DataBuffer m_public_exponent;
	CL_DataBuffer m_modulus;
};

class Crypt_Client
{
public:
	Crypt_Client(TestApp *testapp) : m_pTestApp(testapp)
	{
	}

	void create_keypair()
	{
		CL_RSA::create_keypair(m_Random, m_private_exponent, m_public_exponent, m_modulus);
	}

	void set_crypt_key(const CL_DataBuffer &public_key)
	{
		m_WrappedCryptKey = public_key;
		m_CryptKey = CL_RSA::decrypt(m_private_exponent, m_modulus, public_key);
	}

	TestApp *m_pTestApp;
	CL_Random m_Random;

	CL_DataBuffer m_WrappedCryptKey;
	CL_Secret m_CryptKey;

	CL_Secret m_private_exponent;
	CL_DataBuffer m_public_exponent;
	CL_DataBuffer m_modulus;
};

void TestApp::test_rsa()
{
	CL_Console::write_line(" Header: rsa.h");
	CL_Console::write_line("  Class: CL_RSA");

	CL_Console::write_line("   ... Creating KeyPair (Server)");
	Crypt_Server server(this);
	server.create_keypair();

	CL_Console::write_line("   ... Creating KeyPair (Client)");
	Crypt_Client client(this);
	client.create_keypair();

	CL_Console::write_line("   ... Exchanging keys");

	server.create_crypt_key();
	client.set_crypt_key(server.export_wrap_crypt_key( client.m_public_exponent, client.m_modulus));

	CL_Console::write_line("   ... Running Test");

	if (server.m_CryptKey.get_size() != client.m_CryptKey.get_size() )
		fail();
	if (memcmp(server.m_CryptKey.get_data(), client.m_CryptKey.get_data(), server.m_CryptKey.get_size()))
		fail();

}



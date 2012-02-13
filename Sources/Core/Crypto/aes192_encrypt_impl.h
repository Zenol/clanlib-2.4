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
**    Mark Page
*/

#pragma once

#include "API/Core/System/cl_platform.h"
#include "API/Core/System/databuffer.h"

#include "aes_impl.h"

class CL_AES192_Encrypt_Impl : public CL_AES_Impl
{
/// \name Construction
/// \{

public:
	CL_AES192_Encrypt_Impl();

/// \}
/// \name Attributes
/// \{

	/// \brief Get encrypted data
	///
	/// This is the databuffer used internally to store the encrypted data.
	/// You may call "set_size()" to clear the buffer, inbetween calls to "add()"
	/// You may call "set_capacity()" to optimise storage requirements before the add() call
	CL_DataBuffer get_data() const;

/// \}
/// \name Operations
/// \{

public:
	/// \brief Resets the encryption
	void reset();

	/// \brief Purge the databuffer
	///
	/// See get_data()\n
	/// reset() calls this function
	void purge_data();

	/// \brief Sets the initialisation vector
	///
	/// This must be called before the initial add()
	void set_iv(const unsigned char iv[16]);

	/// \brief Sets the cipher key
	///
	/// This must be called before the initial add()
	void set_key(const unsigned char key[24]);

	void set_padding(bool value, bool use_pkcs7, unsigned int num_additional_padded_blocks);

	/// \brief Adds data to be encrypted
	void add(const void *data, int size);

	/// \brief Add data to be encrypted
	///
	/// \param data = Data Buffer
	void add(const CL_DataBuffer &data);

	/// \brief Finalize decryption
	void calculate();

/// \}
/// \name Implementation
/// \{

private:
	void process_chunk();

	cl_ubyte32 key_expanded[aes192_nb_mult_nr_plus1];

	unsigned char chunk[aes192_block_size_bytes];
	cl_ubyte32 initialisation_vector_1;
	cl_ubyte32 initialisation_vector_2;
	cl_ubyte32 initialisation_vector_3;
	cl_ubyte32 initialisation_vector_4;
	
	int chunk_filled;

	bool initialisation_vector_set;
	bool cipher_key_set;
	bool calculated;
	bool padding_enabled;
	bool padding_pkcs7;
	unsigned int padding_num_additional_padded_blocks;

	CL_DataBuffer databuffer;
/// \}
};



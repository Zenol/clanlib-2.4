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
*/

/// \addtogroup clanCore_I_O_Data clanCore I/O Data
/// \{

#pragma once

class CL_DataBuffer;

/// \brief Deflate compressor
class CL_ZLibCompression
{
/// \name Operations
/// \{
public:
	// \brief Compress data
	// \param data Data to compress
	// \param window_bits Sliding window size
	// \param raw Skips header if true
	// \param compression_level Compression level in range 0-9. 0 = no compression, 1 = best speed, 6 = default, 9 = best compression.
	static CL_DataBuffer compress(const CL_DataBuffer &data, int window_bits = 15, bool raw = true, int compression_level = 6);

	// \brief Decompress data
	// \param data Data to compress
	// \param window_bits Sliding window size
	// \param raw Skips header if true
	static CL_DataBuffer decompress(const CL_DataBuffer &data, int window_bits = 15, bool raw = true);
/// \}
};

/// \}

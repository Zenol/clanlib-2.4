/*
**  ClanLib SDK
**  Copyright (c) 1997-2010 The ClanLib Team
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

#include "D3D10/precomp.h"
#include "d3d10_texture_provider.h"
#include "API/Display/Image/pixel_buffer.h"

/////////////////////////////////////////////////////////////////////////////
// CL_D3D10TextureProvider Construction:

CL_D3D10TextureProvider::CL_D3D10TextureProvider()
{
}

CL_D3D10TextureProvider::~CL_D3D10TextureProvider()
{
}

/////////////////////////////////////////////////////////////////////////////
// CL_D3D10TextureProvider Attributes:

/////////////////////////////////////////////////////////////////////////////
// CL_D3D10TextureProvider Operations:

void CL_D3D10TextureProvider::create(int new_width, int new_height, CL_TextureFormat internal_format, int new_depth)
{
}

void CL_D3D10TextureProvider::destroy()
{
	delete this;
}

CL_PixelBuffer CL_D3D10TextureProvider::get_pixeldata(CL_TextureFormat sized_format, int level) const 
{
	return CL_PixelBuffer();
}

void CL_D3D10TextureProvider::set_image(CL_PixelBuffer &image, int level, CL_TextureFormat internal_format)
{
}

void CL_D3D10TextureProvider::set_cube_map(
	CL_PixelBuffer &cube_map_positive_x,
	CL_PixelBuffer &cube_map_negative_x,
	CL_PixelBuffer &cube_map_positive_y,
	CL_PixelBuffer &cube_map_negative_y,
	CL_PixelBuffer &cube_map_positive_z,
	CL_PixelBuffer &cube_map_negative_z,
	int level,
	CL_TextureFormat internal_format)
{
}

void CL_D3D10TextureProvider::set_compressed_image(
	int level,
	CL_TextureFormat internal_format,
	int width,
	int height,
	CL_DataBuffer &image)
{
}

void CL_D3D10TextureProvider::set_subimage(
	int x,
	int y,
	const CL_PixelBuffer &image,
	const CL_Rect &src_rect,
	int level)
{
}

void CL_D3D10TextureProvider::copy_image_from(
	int x,
	int y,
	int width,
	int height,
	int level,
	CL_TextureFormat internal_format,
	CL_GraphicContextProvider *gc)
{
}

void CL_D3D10TextureProvider::copy_subimage_from(
	int offset_x,
	int offset_y,
	int x,
	int y,
	int width,
	int height,
	int level,
	CL_GraphicContextProvider *gc)
{
}

void CL_D3D10TextureProvider::set_min_lod(double min_lod)
{
}

void CL_D3D10TextureProvider::set_max_lod(double max_lod)
{
}

void CL_D3D10TextureProvider::set_lod_bias(double lod_bias)
{
}

void CL_D3D10TextureProvider::set_base_level(int base_level)
{
}

void CL_D3D10TextureProvider::set_max_level(int max_level)
{
}

void CL_D3D10TextureProvider::set_wrap_mode(
	CL_TextureWrapMode wrap_s,
	CL_TextureWrapMode wrap_t,
	CL_TextureWrapMode wrap_r)
{
}

void CL_D3D10TextureProvider::set_wrap_mode(
	CL_TextureWrapMode wrap_s,
	CL_TextureWrapMode wrap_t)
{
}

void CL_D3D10TextureProvider::set_wrap_mode(
	CL_TextureWrapMode wrap_s)
{
}

void CL_D3D10TextureProvider::set_min_filter(CL_TextureFilter filter)
{
}

void CL_D3D10TextureProvider::set_mag_filter(CL_TextureFilter filter)
{
}

void CL_D3D10TextureProvider::set_max_anisotropy(float v)
{
}

void CL_D3D10TextureProvider::set_texture_compare(CL_TextureCompareMode mode, CL_CompareFunction func)
{
}
/////////////////////////////////////////////////////////////////////////////
// CL_D3D10TextureProvider Implementation:
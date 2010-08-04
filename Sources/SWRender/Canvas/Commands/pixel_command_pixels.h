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

#pragma once

#include "API/SWRender/pixel_command.h"
#include "API/Display/Image/pixel_buffer.h"
#include "API/Display/2D/color.h"

class CL_PixelCommandPixels : public CL_PixelCommand
{
public:
	CL_PixelCommandPixels(const CL_Rect &dest_rect, const CL_PixelBuffer &image, const CL_Rect &src_rect, const CL_Colorf &primary_color);
	void run(CL_PixelThreadContext *context);

private:
	void render_pixels_scale(CL_PixelThreadContext *context, const CL_Rect &box);
	void render_pixels_noscale(CL_PixelThreadContext *context, const CL_Rect &box);
	void render_pixels_noscale_white(CL_PixelThreadContext *context, const CL_Rect &box);
	CL_Rect get_clipped_dest_rect(CL_PixelThreadContext *context) const;

	CL_Rect dest_rect;
	CL_PixelBuffer image;
	CL_Rect src_rect;
	CL_Colorf primary_color;
};
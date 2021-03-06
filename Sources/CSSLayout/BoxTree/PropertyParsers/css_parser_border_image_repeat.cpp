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

#include "CSSLayout/precomp.h"
#include "css_parser_border_image_repeat.h"
#include "API/CSSLayout/css_box_properties.h"

std::vector<CL_String> CL_CSSParserBorderImageRepeat::get_names()
{
	std::vector<CL_String> names;
	names.push_back("border-image-repeat");
	return names;
}

void CL_CSSParserBorderImageRepeat::parse(CL_CSSBoxProperties &properties, const CL_String &name, const std::vector<CL_CSSToken> &tokens, std::map<CL_String, CL_CSSBoxProperty *> *out_change_set)
{
	CL_CSSBoxBorderImageRepeat border_image_repeat;
	border_image_repeat.type = CL_CSSBoxBorderImageRepeat::type_values;

	size_t pos = 0;
	CL_CSSToken token = next_token(pos, tokens);
	if (token.type == CL_CSSToken::type_ident && pos == tokens.size() && equals(token.value, "inherit"))
	{
		properties.border_image_repeat.type = CL_CSSBoxBorderImageRepeat::type_inherit;
		if (out_change_set)
		{
			(*out_change_set)["border-image-repeat"] = &properties.border_image_repeat;
		}
		return;
	}
	else if (token.type == CL_CSSToken::type_ident && equals(token.value, "stretch"))
	{
		border_image_repeat.repeat_x = CL_CSSBoxBorderImageRepeat::repeat_type_stretch;
	}
	else if (token.type == CL_CSSToken::type_ident && equals(token.value, "repeat"))
	{
		border_image_repeat.repeat_x = CL_CSSBoxBorderImageRepeat::repeat_type_repeat;
	}
	else if (token.type == CL_CSSToken::type_ident && equals(token.value, "round"))
	{
		border_image_repeat.repeat_x = CL_CSSBoxBorderImageRepeat::repeat_type_round;
	}
	else
	{
		return;
	}

	if (pos == tokens.size())
	{
		border_image_repeat.repeat_y = border_image_repeat.repeat_x;
		properties.border_image_repeat = border_image_repeat;
	}
	else
	{
		token = next_token(pos, tokens);
		if (token.type == CL_CSSToken::type_ident && equals(token.value, "stretch"))
		{
			border_image_repeat.repeat_y = CL_CSSBoxBorderImageRepeat::repeat_type_stretch;
		}
		else if (token.type == CL_CSSToken::type_ident && equals(token.value, "repeat"))
		{
			border_image_repeat.repeat_y = CL_CSSBoxBorderImageRepeat::repeat_type_repeat;
		}
		else if (token.type == CL_CSSToken::type_ident && equals(token.value, "round"))
		{
			border_image_repeat.repeat_y = CL_CSSBoxBorderImageRepeat::repeat_type_round;
		}
		else
		{
			return;
		}
	}
	if (out_change_set)
	{
		(*out_change_set)["border-image-repeat"] = &properties.border_image_repeat;
	}
}

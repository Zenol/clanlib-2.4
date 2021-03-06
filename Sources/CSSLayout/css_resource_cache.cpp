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
#include "css_resource_cache.h"
#include "API/CSSLayout/css_box_properties.h"
#include "LayoutTree/css_used_value.h"

CL_CSSResourceCache::CL_CSSResourceCache()
{
#ifdef WIN32
	HDC screen_dc = GetDC(0);
	LOGFONT logfont = { 0 };
	logfont.lfFaceName[0] = 0;
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfPitchAndFamily = DEFAULT_PITCH;
	BOOL result = EnumFontFamiliesEx(screen_dc, &logfont, &static_enum_font_families_callback, (LPARAM)this, 0);
	ReleaseDC(0, screen_dc);
#endif
}

CL_CSSResourceCache::~CL_CSSResourceCache()
{
}

#ifdef WIN32
int CL_CSSResourceCache::enum_font_families_callback(const LOGFONTW *fontinfo, const TEXTMETRICW *textmetrics, DWORD font_type)
{
	CL_String name = CL_StringHelp::ucs2_to_utf8(fontinfo->lfFaceName);
	CL_String search_name = CL_StringHelp::text_to_lower(name);
	font_families[search_name] = true;
	return 1;
}

int CL_CSSResourceCache::static_enum_font_families_callback(const LOGFONTW *fontinfo, const TEXTMETRICW *textmetrics, DWORD font_type, LPARAM lparam)
{
	return reinterpret_cast<CL_CSSResourceCache*>(lparam)->enum_font_families_callback(fontinfo, textmetrics, font_type);
}
#endif

CL_Font &CL_CSSResourceCache::get_font(CL_GraphicContext &gc, const CL_CSSBoxProperties &properties)
{
	int font_size = cl_used_to_actual(properties.font_size.length.value);
	CL_String font_name;
	for (size_t i = 0; i < properties.font_family.names.size(); i++)
	{
		bool matched = false;
		CL_String search_name;
		switch (properties.font_family.names[i].type)
		{
		case CL_CSSBoxFontFamilyName::type_family_name:
			search_name = CL_StringHelp::text_to_lower(properties.font_family.names[i].name);
			if (font_families.find(search_name) != font_families.end())
			{
				font_name = properties.font_family.names[i].name;
				matched = true;
			}
			break;
		default:
		case CL_CSSBoxFontFamilyName::type_serif:
		case CL_CSSBoxFontFamilyName::type_cursive:
		case CL_CSSBoxFontFamilyName::type_fantasy:
			font_name = "Times New Roman"; // Ugliest font on the planet.
			matched = true;
			break;
		case CL_CSSBoxFontFamilyName::type_sans_serif:
			font_name = "Arial";
			matched = true;
			break;
		case CL_CSSBoxFontFamilyName::type_monospace:
			font_name = "Courier New";
			matched = true;
			break;
		}
		if (matched)
			break;
	}
	if (font_name.empty())
		font_name = "Times New Roman";

	int font_weight = 400;
	switch (properties.font_weight.type)
	{
	case CL_CSSBoxFontWeight::type_100: font_weight = 100; break;
	case CL_CSSBoxFontWeight::type_200: font_weight = 200; break;
	case CL_CSSBoxFontWeight::type_300: font_weight = 300; break;
	case CL_CSSBoxFontWeight::type_400: font_weight = 400; break;
	case CL_CSSBoxFontWeight::type_500: font_weight = 500; break;
	case CL_CSSBoxFontWeight::type_600: font_weight = 600; break;
	case CL_CSSBoxFontWeight::type_700: font_weight = 700; break;
	case CL_CSSBoxFontWeight::type_800: font_weight = 800; break;
	case CL_CSSBoxFontWeight::type_900: font_weight = 900; break;
	case CL_CSSBoxFontWeight::type_normal: font_weight = 400; break;
	case CL_CSSBoxFontWeight::type_bold: font_weight = 700; break;
	case CL_CSSBoxFontWeight::type_bolder: font_weight = 900; break;
	case CL_CSSBoxFontWeight::type_lighter: font_weight = 300; break;
	}
	bool italic = false;
	switch (properties.font_style.type)
	{
	case CL_CSSBoxFontStyle::type_normal: italic = false; break;
	case CL_CSSBoxFontStyle::type_italic: italic = true; break;
	case CL_CSSBoxFontStyle::type_oblique: italic = true; break;
	}
	CL_String font_cache_name = cl_format("%1+++%2+%3", font_name, font_size, font_weight);
	if (italic) font_cache_name += "i";
	std::map<CL_String, CL_Font>::iterator it = font_cache.find(font_cache_name);
	if (it == font_cache.end())
	{
		CL_FontDescription font_desc;
		font_desc.set_typeface_name(font_name);
		font_desc.set_height(-font_size);
		font_desc.set_weight(font_weight);
		font_desc.set_italic(italic);
		font_cache[font_cache_name] = CL_Font(gc, font_desc);
		return font_cache[font_cache_name];
	}
	else
	{
		return it->second;
	}
}

CL_Image &CL_CSSResourceCache::get_image(CL_GraphicContext &gc, const CL_String &url)
{
	std::map<CL_String, CL_Image>::iterator it = image_cache.find(url);
	if (it == image_cache.end())
	{
		CL_Image image;
		if (!cb_get_image.is_null())
			image = cb_get_image.invoke(gc, url);

		image_cache[url] = image;
		return image_cache[url];
	}
	else
	{
		return it->second;
	}
}

CL_CSSBoxLength CL_CSSResourceCache::compute_length(const CL_CSSBoxLength &length, float em_size, float ex_size)
{
	float dpi = 96.0f;
	float px_size = 1.0f;
/*
	if (is_printer)
	{
		if (printer.dpi == 300)
		{
			dpi = 300.0f;
			px_size = 3.0f;
		}
		else if (printer.dpi == 600)
		{
			dpi = 600.0f;
			px_size = 5.0f;
		}
		else
		{
			dpi = printer.dpi;
			px_size = (float)(int)(0.20f * dpi / 25.4f + 0.5f); // Find the closest pixel size matching 0.20mm
		}
	}
*/
	CL_CSSBoxLength new_length;
	new_length.type = CL_CSSBoxLength::type_computed_px;
	switch (length.type)
	{
	case CL_CSSBoxLength::type_computed_px:
		new_length.value = length.value;
		break;
	case CL_CSSBoxLength::type_mm:
		new_length.value = length.value * dpi / 25.4f;
		break;
	case CL_CSSBoxLength::type_cm:
		new_length.value = length.value * dpi / 2.54f;
		break;
	case CL_CSSBoxLength::type_in:
		new_length.value = length.value * dpi;
		break;
	case CL_CSSBoxLength::type_pt:
		new_length.value = length.value * dpi / 72.0f;
		break;
	case CL_CSSBoxLength::type_pc:
		new_length.value = length.value * dpi * 12.0f / 72.0f;
		break;
	case CL_CSSBoxLength::type_em:
		new_length.value = length.value * em_size;
		break;
	case CL_CSSBoxLength::type_ex:
		new_length.value = length.value * ex_size;
		break;
	case CL_CSSBoxLength::type_px:
		new_length.value = length.value * px_size;
		break;
	default:
		throw CL_Exception("Unknown css length dimension!");
	}
	return new_length;
}

std::vector<CL_String> CL_CSSResourceCache::get_default_quotes()
{
	std::vector<CL_String> values;
	values.push_back("\"");
	values.push_back("\"");
	return values;
}

CL_Colorf CL_CSSResourceCache::get_default_color()
{
	return CL_Colorf::black;
}

CL_CSSBoxLength CL_CSSResourceCache::get_font_table_size(int size)
{
	// To do: Return 13px for Monospace font type (so defaults match Firefox)
	return CL_CSSBoxLength(16.0f, CL_CSSBoxLength::type_px);
}

CL_CSSBoxLength CL_CSSResourceCache::get_font_table_smaller(float em_size)
{
	return CL_CSSBoxLength(14.0f, CL_CSSBoxLength::type_px);
}

CL_CSSBoxLength CL_CSSResourceCache::get_font_table_larger(float em_size)
{
	return CL_CSSBoxLength(18.0f, CL_CSSBoxLength::type_px);
}

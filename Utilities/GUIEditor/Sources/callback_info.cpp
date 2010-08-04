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
**    Harry Storbacka
*/

#include "precomp.h"
#include "callback_info.h"

CallbackInfo::CallbackInfo()
{
	populate();	
}


void CallbackInfo::populate()
{
	// The following was generated by copy-pasting the results of Visual C++ 7.1 find
	// in files for "func_" to callbacks.txt, and removing callbacks not belonging to
	// components. The python script gui_callbacks_listing_to_code.py finally produces what you see here.

	callbacks.push_back(CallbackData("gui_component", "render", "CL_GraphicContext &", " const CL_Rect &"));
	callbacks.push_back(CallbackData("gui_component", "process_message", "CL_GUIMessage &", ""));
	callbacks.push_back(CallbackData("gui_component", "style_changed", "", ""));
	callbacks.push_back(CallbackData("gui_component", "enablemode_changed", "", ""));
	callbacks.push_back(CallbackData("gui_component", "resized", "", ""));
	callbacks.push_back(CallbackData("gui_component", "constrain_resize", "CL_Rect &", ""));
	callbacks.push_back(CallbackData("gui_component", "create_custom_component", "", ""));
	callbacks.push_back(CallbackData("checkbox", "checked", "", ""));
	callbacks.push_back(CallbackData("checkbox", "unchecked", "", ""));
	callbacks.push_back(CallbackData("checkbox", "indeterminated", "", ""));
	callbacks.push_back(CallbackData("checkbox", "state_changed", "", ""));
	callbacks.push_back(CallbackData("combobox", "dropdown_opened", "", ""));
	callbacks.push_back(CallbackData("combobox", "dropdown_closed", "", ""));
	callbacks.push_back(CallbackData("combobox", "before_edit_changed", "", ""));
	callbacks.push_back(CallbackData("combobox", "after_edit_changed", "", ""));
	callbacks.push_back(CallbackData("combobox", "lineedit_unhandled_event", "CL_InputEvent", ""));
	callbacks.push_back(CallbackData("combobox", "display_popup", "CL_Rect", ""));
	callbacks.push_back(CallbackData("combobox", "item_selected", "int", ""));
	callbacks.push_back(CallbackData("combobox", "selection_changed", "int", ""));
	callbacks.push_back(CallbackData("lineedit", "before_edit_changed", "CL_InputEvent", ""));
	callbacks.push_back(CallbackData("lineedit", "after_edit_changed", "CL_InputEvent", ""));
	callbacks.push_back(CallbackData("lineedit", "selection_changed", "", ""));
	callbacks.push_back(CallbackData("lineedit", "focus_gained", "", ""));
	callbacks.push_back(CallbackData("lineedit", "unhandled_event", "CL_InputEvent", ""));
	callbacks.push_back(CallbackData("listview", "selection_changed", "CL_ListViewSelection", ""));
	callbacks.push_back(CallbackData("listview", "item_edited", "CL_ListViewItem", ""));
	callbacks.push_back(CallbackData("listview", "key_pressed", "CL_InputEvent", ""));
	callbacks.push_back(CallbackData("listview", "key_released", "CL_InputEvent", ""));
	callbacks.push_back(CallbackData("push_button", "clicked", "", ""));
	callbacks.push_back(CallbackData("radiobutton", "selected", "", ""));
	callbacks.push_back(CallbackData("radiobutton", "unselected", "", ""));
	callbacks.push_back(CallbackData("radiobutton", "group_selection_changed", "CL_RadioButton*", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_min", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_max", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_line_decrement", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_line_increment", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_page_decrement", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_page_increment", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_thumb_position", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_thumb_track", "", ""));
	callbacks.push_back(CallbackData("scrollbar", "scroll_end", "", ""));
	callbacks.push_back(CallbackData("slider", "slider_value_changed", "", ""));
	callbacks.push_back(CallbackData("slider", "slider_decremented", "", ""));
	callbacks.push_back(CallbackData("slider", "slider_incremented", "", ""));
	callbacks.push_back(CallbackData("slider", "slider_moved", "", ""));
	callbacks.push_back(CallbackData("spin", "value_changed", "", ""));
	callbacks.push_back(CallbackData("statusbar", "part_double_clicked", "", ""));
	callbacks.push_back(CallbackData("toolbar", "item_clicked", "CL_ToolBarItem", ""));
	callbacks.push_back(CallbackData("toolbar", "item_selected", "CL_ToolBarItem", ""));
	callbacks.push_back(CallbackData("toolbar", "item_unselected", "CL_ToolBarItem", ""));
	callbacks.push_back(CallbackData("window", "close", "", ""));
	callbacks.push_back(CallbackData("window", "resize", "CL_Rect&", ""));
}

std::vector<CallbackData> CallbackInfo::get_callbacks( const CL_StringRef &comp_type )
{
	std::vector<CallbackData> retval;
	std::vector<CallbackData>::iterator it;
	for (it = callbacks.begin(); it != callbacks.end(); ++it)
	{
		if ((*it).get_component_type() == comp_type)
		{
			retval.push_back((*it));
		}
	}
	return retval;
}
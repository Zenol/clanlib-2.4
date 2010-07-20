#include <ClanLib/core.h>
#include <ClanLib/gui.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

class App
{
public:
	CL_Label *label;

	int main(const std::vector<CL_String> &args)
	{
		try
		{
			CL_GUIManager gui;

			CL_ResourceManager resources("../../../Resources/GUIThemeLuna/resources.xml");

			CL_GUIWindowManagerSystem wm;
			gui.set_window_manager(wm);

			CL_GUIThemeDefault theme;
			theme.set_resources(resources);
			gui.set_theme(theme); 
			gui.set_css_document("../../../Resources/GUIThemeLuna/theme.css");

			CL_DisplayWindowDescription win_desc;
			win_desc.set_allow_resize(true);
			win_desc.set_title("Button WM System Test Application");
			win_desc.set_position(CL_RectPS(200, 200, 640, 520), false);
			CL_Window window(&gui, win_desc);
			window.func_close().set(this, &App::on_close, &window);
			
			CL_LineEdit lineedit(&window);
			lineedit.set_geometry(CL_RectPS(300,300,100,21));

			CL_PushButton button(&window);
			button.set_geometry(CL_RectPS(640-10-80-10-80, 480-10-21, 80, 21));
			button.set_text("Ok");
			button.set_default(true);
			
			CL_PushButton button2(&window);
			button2.set_geometry(CL_RectPS(640-10-80, 480-10-21, 80, 21));
			button2.set_text("Cancel");
			
			gui.exec();
		}
		catch (CL_Exception e)
		{
			CL_ConsoleWindow console("Console");
			CL_Console::write_line(e.message);
			console.display_close_message();
		}

		return 0;
	}

	void on_button_clicked(CL_PushButton *button)
	{
		label->set_text("You clicked " + button->get_text());
	}

	bool on_close(CL_Window *win)
	{
		win->exit_with_code(0);
		return true;
	}
};

// This is the Program class that is called by CL_ClanApplication
class Program
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;

		// Start the Application
		App app;
		int retval = app.main(args);
		return retval;
	}
};

// Instantiate CL_ClanApplication, informing it where the Program is located
CL_ClanApplication app(&Program::main);


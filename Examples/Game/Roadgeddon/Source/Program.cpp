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
**    Arkadiusz Kalinowski
*/

#include "Precomp.h"
#include "Program.h"
#include "Game.h"


int Program::main(const std::vector<CL_String> &args)
{
	try
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;

		CL_SetupSound setup_sound;
		CL_SetupVorbis setup_vorbis;
	 
		CL_SoundOutput output(44100);

		// You can change the display target in precomp.h

		#ifdef USE_SOFTWARE_RENDERER
		CL_SetupSWRender setup_swrender;
		#endif

		#ifdef USE_OPENGL_1
		CL_SetupGL1 setup_gl1;
		#endif

		#ifdef USE_OPENGL_2
		CL_SetupGL setup_gl;
		#endif

		//CL_ConsoleLogger logger;

		Game game;
		game.run();
		return 0;
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();

		return -1;
	}
}

// Instantiate CL_ClanApplication, informing it where the Program is located
CL_ClanApplication app(&Program::main);

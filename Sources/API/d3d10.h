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
**    Kenneth Gangstoe
*/

/// \brief <p>ClanLib D3D10 target library.</p>
//! Global=D3D10

#pragma once

#ifdef __cplusplus_cli
#pragma managed(push, off)
#endif

#include "D3D10/d3d10_target.h"
#include "D3D10/setup_d3d10.h"

#ifdef __cplusplus_cli
#pragma managed(pop)
#endif

#if defined (_MSC_VER)
	#if !defined (UNICODE)
		#if defined (CL_DLL)
			#if !defined (_DEBUG)
				#pragma comment(lib, "clanD3D10-dll.lib")
			#else
				#pragma comment(lib, "clanD3D10-dll-debug.lib")
			#endif
		#elif defined (_DLL)
			#if !defined (_DEBUG)
				#pragma comment(lib, "clanD3D10-static-mtdll.lib")
			#else
				#pragma comment(lib, "clanD3D10-static-mtdll-debug.lib")
			#endif
			#pragma comment(lib, "winmm.lib")
			#pragma comment(lib, "dinput8.lib")
			#pragma comment(lib, "dxguid.lib")
		#else
			#if !defined (_DEBUG)
				#pragma comment(lib, "clanD3D10-static-mt.lib")
			#else
				#pragma comment(lib, "clanD3D10-static-mt-debug.lib")
			#endif
			#pragma comment(lib, "winmm.lib")
			#pragma comment(lib, "dinput8.lib")
			#pragma comment(lib, "dxguid.lib")
		#endif
	#else
		#if defined (CL_DLL)
			#if !defined (_DEBUG)
				#pragma comment(lib, "clanD3D10-dll-uc.lib")
			#else
				#pragma comment(lib, "clanD3D10-dll-uc-debug.lib")
			#endif
		#elif defined (_DLL)
			#if !defined (_DEBUG)
				#pragma comment(lib, "clanD3D10-static-mtdll-uc.lib")
			#else
				#pragma comment(lib, "clanD3D10-static-mtdll-uc-debug.lib")
			#endif
			#pragma comment(lib, "winmm.lib")
			#pragma comment(lib, "dinput8.lib")
			#pragma comment(lib, "dxguid.lib")
		#else
			#if !defined (_DEBUG)
				#pragma comment(lib, "clanD3D10-static-mt-uc.lib")
			#else
				#pragma comment(lib, "clanD3D10-static-mt-uc-debug.lib")
			#endif
			#pragma comment(lib, "winmm.lib")
			#pragma comment(lib, "dinput8.lib")
			#pragma comment(lib, "dxguid.lib")
		#endif
	#endif
#endif


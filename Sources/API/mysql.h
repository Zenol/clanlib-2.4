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

/// \brief <p>ClanLib MySQL database connection library.</p>
//! Global=MySQL

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif

#include "MySQL/mysql_connection.h"

#if defined (_MSC_VER)
	#if defined (CL_DLL)
		#if !defined (_DEBUG)
			#pragma comment(lib, "clanMySQL-dll.lib")
		#else
			#pragma comment(lib, "clanMySQL-dll-debug.lib")
		#endif
	#elif defined (CL_STATIC_MTDLL)
		#if !defined (_DEBUG)
			#pragma comment(lib, "clanMySQL-static-mtdll.lib")
		#else
			#pragma comment(lib, "clanMySQL-static-mtdll-debug.lib")
		#endif
		#pragma comment(lib, "mysql.lib")
	#else
		#if !defined (_DEBUG)
			#pragma comment(lib, "clanMySQL-static-mt.lib")
		#else
			#pragma comment(lib, "clanMySQL-static-mt-debug.lib")
		#endif
		#pragma comment(lib, "mysql.lib")
	#endif
#endif


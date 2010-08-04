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

/// \addtogroup clanD3D10_System clanD3D10 System
/// \{

#pragma once

#include "api_d3d10.h"

/// \brief ClanD3D10 initialization functions.
///
/// \xmlonly !group=D3D10/System! !header=d3d10.h! \endxmlonly
class CL_API_D3D10 CL_SetupD3D10
{
/// \name Construction
/// \{

public:
	/// \brief Initializes clanD3D10.
	CL_SetupD3D10();

	~CL_SetupD3D10();
/// \}
};

/// \}
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
**    Mark Page
*/

/// \addtogroup clanSound_Audio_Mixing clanSound Audio Mixing
/// \{

#pragma once

#include "../api_sound.h"

/// \brief Sound Filter Interface
///
/// \xmlonly !group=Sound/Audio Mixing! !header=sound.h! \endxmlonly
class CL_API_SOUND CL_SoundFilterProvider
{
/// \name Construction
/// \{

public:
	virtual ~CL_SoundFilterProvider() { return; }

/// \}
/// \name Operations
/// \{

public:
	/// \brief Destroys the provider.
	virtual void destroy() = 0;

	/// \brief Filter callback.
	/** <p>All sound data is passed through this function,
	    which modifies the sample data accordingly to the function of the
	    filter.</p>
	    <p>The format of the sample data is always 16 bit stereo. </p>*/
	virtual void filter(float **sample_data, int num_samples, int channels)=0;

/// \}
/// \name Implementation
/// \{

public:
/// \}
};

/// \}

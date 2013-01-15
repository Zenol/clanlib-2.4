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

#pragma once
#include "Precomp.h"
#include "Game.h"

class Map
{
//_____________________________________________________________________________________
//																C O N S T R U C T O R S
public:
	Map(Game &game_);
	~Map();

//_________________________________________________________________________________
//																O P E R A T I O N S
	void draw();
	void drawBackground();
	void update(int time_elapsed_ms);
//_________________________________________________________________________________
//																A T T R I B U T E S
private:
	Game *game;
	
	CL_Slot update_slot;
	CL_Slot draw_slot;

	CL_Sprite *title1;
	CL_Sprite *background1;
	CL_Sprite *background2;

	CL_Vec2f back1_pos;
	CL_Vec2f back2_pos;
	float pos_x,pos_y;

};
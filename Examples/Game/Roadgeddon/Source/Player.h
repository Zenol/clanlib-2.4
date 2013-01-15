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
#include "Missile.h"

class Player : public Gameobject
{
//_________________________________________________________________________
//																S T A T I C
public:
	static Player *getPlayer1();

private:
	static bool isPlayer1Playing;
	static Player *player1;

//_____________________________________________________________________________________
//																C O N S T R U C T O R S

public:
	Player(Game &game);
	~Player();

	
//_________________________________________________________________________________
//																A T T R I B U T E S
	CL_CollisionOutline &get_collision_outline() { return col_out; }
	CL_Vec2f getPos();
//_________________________________________________________________________________
//																O P E R A T I O N S
public:
	void draw();
	void update(int time_elapsed_ms);
	void hurt(float damage);

	void aimAt	(int x, int y);
	void right	(bool state);
	void up		(bool state);
	void left	(bool state);
	void down	(bool state);
	void shoot1	(bool state);
	void shoot2 (bool state);

private:
	void aim_turret();
//_________________________________________________________________________________________
//																I M P L E M E N T A T I O N
private:
	
	//Turret
	CL_Sprite *turret;
	CL_Angle turret_angle;
	CL_Vec2f turretPos;
	CL_Sprite *turretBase;
	MissileDesc missile;
	//

	CL_CollisionOutline col_out;

	CL_Sprite *vehicle;
	Game *game;

	CL_Slot draw_slot;
	CL_Slot update_slot;

	float max_life;
	float life;
	bool is_dead;

	bool go_up;
	bool go_right;
	bool go_down;
	bool go_left;
	bool doShoot1;
	bool doShoot2;
	float time_since_last_shoot;
	float x_max_speed,y_max_speed;
	float xAcc,yAcc;
	float x_speed,y_speed;
	float pos_x,pos_y;
	float target_x_pos, target_y_pos;

};
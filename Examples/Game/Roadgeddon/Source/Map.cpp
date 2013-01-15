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

#include "Map.h"
#include "Game.h"

Map::Map(Game &game_)
{
	game = &game_;
	CL_GraphicContext &gc = game_.get_gc(); 
	CL_ResourceManager &resources = game_.get_resources();
	title1 = new CL_Sprite(gc,"Map1",&resources);
	background1 = new CL_Sprite(gc,"Background1",&resources);
	background2 = new CL_Sprite(gc,"Background2",&resources);

	update_slot = game_.get_update_sig().connect(this,&Map::update);

	pos_x= 0;
	pos_y= 0;

	back1_pos.x = 0;
	back1_pos.y = 50;

	back2_pos.x = 0;
	back2_pos.y = 50;
}

Map::~Map()
{
	if(title1!=NULL) delete title1;
	if(background1!=NULL) delete background1;
	if(background2!=NULL) delete background2;
}

void Map::update(int time_elapsed_ms)
{
	pos_x		-= time_elapsed_ms*0.2f;
	back1_pos.x -= time_elapsed_ms*0.1f;
	back2_pos.x -= time_elapsed_ms*0.05f;

	if(pos_x<-256)			pos_x = pos_x+256;
	if(back1_pos.x<-512)	back1_pos.x = back1_pos.x+512;
	if(back2_pos.x<-256)	back2_pos.x = back2_pos.x+256;

}
void Map::draw()
{

}
void Map::drawBackground()
{
	CL_GraphicContext &gc = game->get_gc(); 
	
	int xRes,yRes;
	game->get_screen_resolution(xRes,yRes);
	CL_Gradient gColor(CL_Colorf::lightblue,CL_Colorf::darkblue);
	CL_Draw::gradient_fill(gc,0,0,xRes,yRes,gColor);

	int yDrawPos = yRes;
	for(int i=0;i<4;i++)
	{
		background2->draw(gc,(int)(256*i+back2_pos.x), (int)(yDrawPos-back2_pos.y));
	}
	for(int i=0;i<3;i++)
	{
		background1->draw(gc,(int)(512*i+back1_pos.x), (int)(yDrawPos-back1_pos.y));
	}
	for(int i=0;i<4;i++)
	{
		title1->draw(gc,(int)(256*i+pos_x),yDrawPos);
	}
}
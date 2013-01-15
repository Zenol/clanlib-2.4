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
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Gameobject.h"
#include <list>
#include <vector>
#include "Enemy.h"

Game::Game()
: quit(false)
{
}

Game::~Game()
{
}

void Game::run()
{	

	//_________________________________________________________________
	//										V I D E O   S E T T I N G S
	screen_x_res = 640;
	screen_y_res = 480;

	CL_DisplayWindowDescription desc;
	desc.set_title("Roadgeddon");
	desc.set_size(CL_Size(screen_x_res, screen_y_res), true);
	desc.set_allow_resize(false);

	CL_DisplayWindow window(desc);
	
	CL_Slot slot_quit				= window.sig_window_close()							.connect(this,&Game::on_quit);
	CL_Slot slot_keyboard_key_down	= (window.get_ic().get_keyboard()).sig_key_down()	.connect(this,&Game::on_key_down);
	CL_Slot slot_keyboard_key_up	= (window.get_ic().get_keyboard()).sig_key_up()		.connect(this,&Game::on_key_up);
	CL_Slot slot_mouse_moved		= (window.get_ic().get_mouse()).sig_pointer_move()	.connect(this,&Game::on_pointer_move);
	CL_Slot slot_mouse_down			= (window.get_ic().get_mouse()).sig_key_down()		.connect(this,&Game::on_pointer_down);
	CL_Slot slot_mouse_up			= (window.get_ic().get_mouse()).sig_key_up()		.connect(this,&Game::on_pointer_up);
	
	gc = window.get_gc();

	CL_ResourceManager resources("resources.xml");
	resources_=&resources;

	int time_elapsed_ms = 0;
	int lastTime = 0;
	int currentTime = 0;
	currentTime = CL_System::get_time();
	lastTime = CL_System::get_time();

	//________________________________________________________________
	//											           S O U N D S

	total_channels=3;
	current_channel=1;
	CL_SoundBuffer music("Music1",&resources);
	music.set_volume(0.3f);

	sound_session1.play();
	sound_session2.play();
	sound_session3.play();

	total_samples = 6;
	samples.resize(total_samples);
	samples[0] = CL_SoundBuffer("Explosion1",&resources);
	samples[1] = CL_SoundBuffer("Explosion2",&resources);
	samples[2] = CL_SoundBuffer("Hurt1",&resources);
	samples[3] = CL_SoundBuffer("Hurt2",&resources);
	samples[4] = CL_SoundBuffer("Powerup1",&resources);
	samples[5] = CL_SoundBuffer("Shoot1",&resources);
	
	for(int i = 0; i<total_samples; i++)
	{
		samples[i].set_volume(0.3f);
	}
	
	CL_SoundBuffer_Session music_session = music.prepare();
	music_session_ = &music_session;

	music_session.set_looping(true);
	music_session.play();
	is_music_muted = false;

	//________________________________________________________________
	//											     G A M E   P R E P
	
	Map map(*this);
	Player player(*this);

	mapP = &map;
	playerP = &player;

	time_elapsed_since_last_enemy=0;
	
	//________________________________________________________________
	//														 O T H E R 
	srand(CL_System::get_time());

	while (!quit)
	{
		currentTime = CL_System::get_time();
		time_elapsed_ms = currentTime - lastTime; 
		lastTime = currentTime;
	
		update_game(time_elapsed_ms);
		update_signal.invoke(time_elapsed_ms);

		map.drawBackground();
		draw_signal.invoke();

		// Flip the display, showing on the screen what we have drawed since last call to flip()
		window.flip(1);

		// This call processes user input and other events
		CL_KeepAlive::process(0);

		// Sleep for a little while to avoid using too much of the CPU.
		CL_System::sleep(5);

		if(objects_for_deletion.size()>0)
		{
			std::list<Gameobject *>::iterator it;
			for(it=objects_for_deletion.begin(); it!= objects_for_deletion.end(); ++it)
			{
				delete (*it);
			}

			objects_for_deletion.clear();
		}
	}
}

void Game::on_quit()
{
	quit = true;
}
CL_GraphicContext &Game::get_gc()
{
	return gc;
}
CL_ResourceManager &Game::get_resources()
{
	return *resources_;
}
void Game::get_screen_resolution(int &xRes, int &yRes)
{
	xRes = screen_x_res;
	yRes = screen_y_res;
}

void Game::on_key_down(const CL_InputEvent &key, const CL_InputState &state)
{

	if(key.id==CL_KEY_W) playerP->up(true);
	else if(key.id==CL_KEY_S) playerP->down(true);
	else if(key.id==CL_KEY_A) playerP->left(true);
	else if(key.id==CL_KEY_D) playerP->right(true);
	else if(key.id==CL_KEY_M) mute_music();
	else if(key.id==CL_KEY_ESCAPE) on_quit();

}
void Game::on_key_up(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id==CL_KEY_W) playerP->up(false);
	else if(key.id==CL_KEY_S) playerP->down(false);
	else if(key.id==CL_KEY_A) playerP->left(false);
	else if(key.id==CL_KEY_D) playerP->right(false);

}
void Game::on_pointer_move(const CL_InputEvent &key, const CL_InputState &state)
{
	playerP->aimAt(key.mouse_pos.x,key.mouse_pos.y);
}
void Game::on_pointer_down(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id==CL_MOUSE_LEFT)
	{
		playerP->shoot1(true);
	}
	if(key.id==CL_MOUSE_RIGHT)
	{
		playerP->shoot2(true);
	}
}
void Game::on_pointer_up(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id==CL_MOUSE_LEFT)
	{
		playerP->shoot1(false);
	}
	if(key.id==CL_MOUSE_RIGHT)
	{
		playerP->shoot2(false);
	}
}
void Game::mute_music()
{
	if(is_music_muted)
	{
		if(!music_session_->is_playing())
		{
			music_session_->play();
			is_music_muted=false;
		}
	}
	else
	{
		if(music_session_->is_playing())
		{
			music_session_->stop();
			is_music_muted=true;
		}
	}
}
void Game::add_for_deletion(Gameobject *gameobject)
{
	objects_for_deletion.push_back(gameobject);
}

void Game::update_game(int time_elapsed_ms)
{
	time_elapsed_since_last_enemy+=time_elapsed_ms;

	if(time_elapsed_since_last_enemy>2000)
	{
		Enemy *enemy = new Enemy(*this);
		enemy->set_pos(screen_x_res+100,screen_y_res-128-rand()%(screen_y_res-128));
		time_elapsed_since_last_enemy=0;
	}
}

void Game::play_sample(int ID)
{
	//	0 - Explosion1
	//  1 - Explosion2
	//  2 - Hurt1
	//  3 - Hurt2
	//  4 - Powerup1
	//  5 - Shoot1

	if(ID>=0&&ID<total_samples)
	{
		if(current_channel==1) 
		{
			sound_session1 = samples[ID].prepare();
			sound_session1.play();
		}
		else if(current_channel==2) 
		{
			sound_session2 = samples[ID].prepare();
			sound_session2.play();
		}
		else if(current_channel==3) 
		{
			sound_session3 = samples[ID].prepare();
			sound_session3.play();
		}
		
		current_channel++;
		
		if(current_channel>total_channels)
		{
			current_channel=1;
		}
	}

}
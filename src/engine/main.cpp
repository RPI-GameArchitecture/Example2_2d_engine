/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "framework/ga_compiler_defines.h"
#include "framework/ga_input.h"
#include "framework/ga_sim.h"
#include "framework/ga_output.h"
#include "jobs/ga_job.h"

#include "entity/ga_entity.h"
#include "entity/ga_sprite_component.h"
#include "entity/ga_spriterender_component.h"

#include "entity/item_component.h"
#include "entity/player_component.h"



void create_sprites(ga_sim* sim)
{
	for (int i = 0; i < 100; i++)
	{
		ga_entity* ent = new ga_entity();
		std::string name = "Sprite ";
		name += char('A' + i);
		auto sprite = new ga_sprite_component(ent, i * 30, rand() % 720);

		sprite->_collision_type = 1;
		sprite->_collision_mask = 0;

		auto render = new ga_spriterender_component(ent, "Fruit.png");
		render->_rect.w = 64;
		render->_rect.h = 64;
		render->_rect.x = rand() % 4 * 64;
		render->_rect.y = rand() % 4 * 64;
		sprite->_rect.w = 64;
		sprite->_rect.h = 64;
		auto item = new item_component(ent);
		sim->add_entity(ent);
	}
}
void create_player(ga_sim* sim)
{
	// create one player entity

	ga_entity* player = new ga_entity();
	auto sprite = new ga_sprite_component(player, 800, 500);
	sprite->_collision_type = 2;
	sprite->_collision_mask = 1;

	auto render = new ga_spriterender_component(player,"slime_monster_spritesheet.png");
	render->_rect.w = 97;
	render->_rect.h = 90;
	render->_rect.x = 145;
	render->_rect.y = 275;

	auto ctrl = new player_component(player);
	sim->add_entity(player);
}


// fix for symbol error caused by SDL

#undef main 

int main(int argc, const char** argv)
{
	ga_job::startup(0xffff, 256, 256);

	// Create objects for three phases of the frame: input, sim and output.
	ga_input* input = new ga_input();
	ga_sim* sim = new ga_sim();
	ga_output* output = new ga_output(input->get_window());

	// Run queue unit tests.
	extern void ga_queue_tests();
	ga_queue_tests();

	// Create entities
	
	create_sprites(sim);
	create_player(sim);
	
	// Main loop:
	while (true)
	{
		// We pass frame state through the 3 phases using a params object.
		ga_frame_params params;

		// Gather user input and current time.
		if (!input->update(&params))
		{
			break;
		}

		// Run gameplay.
		sim->update(&params);

		// Draw to screen.
		output->update(&params);

		sim->post_update(&params);
	}

	delete output;
	delete sim;
	delete input;

	ga_job::shutdown();

	return 0;
}

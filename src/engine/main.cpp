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

	// Create test entities.

	ga_entity ents[10];
	for (int i=0;i<10;i++)
	{
		std::string name = "Hello from entity ";
		name += char(i) + 'A';
		auto sprite = new ga_sprite_component(&ents[i], i * 20, 50);
		auto render = new ga_spriterender_component(&ents[i], 15, 15, 255, 0, 0);
		ents[i].add_component(sprite);
		ents[i].add_component(render);
		sim->add_entity(&ents[i]);
	}

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
	}

	delete output;
	delete sim;
	delete input;

	ga_job::shutdown();

	return 0;
}

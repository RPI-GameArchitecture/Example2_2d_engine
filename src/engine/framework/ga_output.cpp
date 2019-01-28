/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_output.h"

#include "ga_frame_params.h"

#include <cassert>
#include <iostream>
#include <SDL.h>

#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>

ga_output::ga_output(void* win) : _window(win)
{
	int width, height;
	SDL_GetWindowSize(static_cast<SDL_Window* >(_window), &width, &height);

	glViewport(0, 0, width, height);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

ga_output::~ga_output()
{
}

void ga_output::update(ga_frame_params* params)
{
	// Update viewport in case window was resized:
	int width, height;
	SDL_GetWindowSize(static_cast<SDL_Window* >(_window), &width, &height);
	glViewport(0, 0, width, height);

	// Clear viewport:
	SDL_Surface* screen_surface = SDL_GetWindowSurface(static_cast<SDL_Window*>(_window));
	SDL_FillRect(screen_surface, NULL, SDL_MapRGBA(screen_surface->format, 128, 255, 128, 255));


	// Draw everything:
	for (auto& d : params->_drawcalls)
	{
		SDL_BlitSurface(d._surf, &d._src_rect, screen_surface, &d._dst_rect);
	}

	GLenum error = glGetError();
	assert(error == GL_NONE);

	// Swap frame buffers:
	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(_window));
}

#include "ga_spriterender_component.h"
#include "ga_entity.h"
#include "framework/ga_drawcall.h"
#include "SDL_Image.h"
#include <SDL.h>
ga_spriterender_component::ga_spriterender_component(ga_entity* ent, int w, int h, int r, int g, int b) : ga_component(ent)
{

	_sprite = ent->get_component<ga_sprite_component>();
	// construct a surface with given width, height, and color

	// flags,width,height,bit depth,channel masks (0=default)
	_sprite_surface = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);

	_rect.x = 0;
	_rect.y = 0;
	_rect.w = w;
	_rect.h = h;

	_color = SDL_MapRGB(_sprite_surface->format, r, g, b);
	SDL_FillRect(_sprite_surface, &_rect, _color);
}

ga_spriterender_component::ga_spriterender_component(ga_entity* ent, const char* path) :  ga_component(ent)
{
	_sprite = ent->get_component<ga_sprite_component>();
	SDL_Surface* tmp_surface = IMG_Load(path);
	// input surface, format, flags
	_rect.x = 0;
	_rect.y = 0;
	_rect.w = 0;
	_rect.h = 0;
	if (tmp_surface)
	{
		_sprite_surface = SDL_ConvertSurfaceFormat(tmp_surface, SDL_PIXELFORMAT_RGBA8888, 0);
	}
	else
	{
		_sprite_surface = nullptr;
	}

	if (_sprite != nullptr && _sprite_surface != nullptr)
	{
		_rect.w= _sprite_surface->w;
		_rect.h = _sprite_surface->h;
		_sprite->_rect.w = _sprite_surface->w;
		_sprite->_rect.h = _sprite_surface->h;
	}
	SDL_FreeSurface(tmp_surface);



}
ga_spriterender_component::~ga_spriterender_component()
{
	// free the surface
	if (_sprite_surface)
	{
		SDL_FreeSurface(_sprite_surface);
	}
}

void ga_spriterender_component::update(struct ga_frame_params* params)
{
	ga_drawcall draw;
	draw._surf = _sprite_surface;
	draw._src_rect = _rect;

	if (_sprite != nullptr)
	{
		draw._dst_rect = _sprite->_rect;
	}
	else
	{
		draw._dst_rect = _rect;
	}


	while (params->_drawcall_lock.test_and_set(std::memory_order_acquire)) {}
	params->_drawcalls.push_back(draw);
	params->_drawcall_lock.clear(std::memory_order_release);

}
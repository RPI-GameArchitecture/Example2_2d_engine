#include "ga_sprite_component.h"

ga_sprite_component::ga_sprite_component(ga_entity* ent, int x, int y) : ga_component(ent)
{
	_x = x;
	_y = y;
	_rect.x = x;
	_rect.y = y;
	_rect.w = 0;
	_rect.h = 0;

}

ga_sprite_component::~ga_sprite_component()
{

}

void ga_sprite_component::update(ga_frame_params* params)
{

}

void ga_sprite_component::set_position(int x, int y)
{
	_x = x;
	_y = y;
	_rect.x = x;
	_rect.y = y;

}

void ga_sprite_component::set_rect(int x, int y, int w, int h)
{
	_x = x;
	_y = y;
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
}
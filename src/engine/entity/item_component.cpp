#include "item_component.h"
#include "ga_sprite_component.h"
#include "ga_entity.h"
#include "framework/ga_sim.h"

item_component::item_component(ga_entity* ent) : ga_component(ent)
{
	_sprite = ent->get_component<ga_sprite_component>();
	_dx = rand() % 10;
	_dy = rand() % 10;
}

item_component::~item_component()
{

}

void item_component::update(ga_frame_params* params)
{
	if (_sprite != nullptr)
	{
		int x = _sprite->_x + _dx;
		if (x > 1280)
		{
			params->_sim->destroy_entity(_entity);
		}
		
		int y = _sprite->_y + _dy;
		if (y > 720) y -= 720;

		_sprite->set_position(x, y);
	}
}
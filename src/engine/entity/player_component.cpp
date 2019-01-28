#include "player_component.h"
#include "ga_entity.h"
#include "ga_sprite_component.h"
#include "../framework/ga_frame_params.h"

player_component::player_component(ga_entity* ent) : public ga_component(ent)
{
	_sprite = ent->get_component<ga_sprite_component>();
	_xspeed = 5;
	_yspeed = 5;
}

player_component::~ga_component()
{

}

void player_component::update(ga_frame_params* params)
{
	if (_sprite != nullptr)
	{
		int x = _sprite->_x;
		int y = _sprite->_y;

		if (params->_button_mask & k_button_right)
		{
			x += _xspeed;
		}
		if (params->_button_mask & k_button_left)
		{
			x -= _xspeed;
		}
		if (params->_button_mask & k_button_down)
		{
			y += _yspeed;
		}
		if (params->_button_mask & k_button_up)
		{
			y -= _yspeed;
		}
		_sprite->set_position(x, y);
	}
}


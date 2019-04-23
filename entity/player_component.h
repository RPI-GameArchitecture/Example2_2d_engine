#pragma once

#include "ga_component.h"
#include "ga_sprite_component.h"
class player_component : public ga_component
{
public:
	player_component (class ga_entity* ent);
	~player_component ();
	virtual void update(struct ga_frame_params* params);

private:
	class ga_sprite_component* _sprite;
	int _xspeed;
	int _yspeed;

};
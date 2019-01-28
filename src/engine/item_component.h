#pragma once

#include "entity/ga_component.h"
class item_component : public ga_component
{
public:

	item_component(class ga_entity* ent);
	~item_component();

	virtual void update(struct ga_frame_params* params) override;

private:
	int _dx;
	int _dy;
	class ga_sprite_component* _sprite;

};
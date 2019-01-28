#pragma once
#include "ga_component.h"

class ga_sprite_component : public ga_component
{
public:
	ga_sprite_component(class ga_entity* ent);
	~ga_sprite_component();

	virtual void update(struct ga_frame_params* params) override;

};
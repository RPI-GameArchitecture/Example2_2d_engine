#pragma once
#include "ga_component.h"
#include <SDL.h>
class ga_sprite_component : public ga_component
{
public:
	int _x;			// position on screen
	int _y;
	SDL_Rect _rect; // bounds rect on screen

	ga_sprite_component(class ga_entity* ent, int x, int y);
	~ga_sprite_component();


	virtual void update(struct ga_frame_params* params) override;
	void set_position(int x, int y);
	void set_rect(int x, int y, int w, int h);

	void check_collisions(ga_sim* sim);
	Uint32 _collision_type;			// my collision flag bit
	Uint32 _collision_mask;			// bitmask of other sprites I can collide with
};
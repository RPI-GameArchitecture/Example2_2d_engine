#pragma once

/*
**
** Draw the sprite.  Manage an SDL surface, load image, construct draw call for blitting
**
*/
#include "ga_component.h"
#include "ga_sprite_component.h"

#include <SDL.h>
class ga_spriterender_component : public ga_component
{
public:
	SDL_Surface * _sprite_surface;
	SDL_Rect _rect; // source rect to use within _sprite_surface

	// construct a sprite with solid color rectangle
	ga_spriterender_component(class ga_entity* ent, int w, int h, int r, int g, int b);
	~ga_spriterender_component();

	virtual void update(struct ga_frame_params* params) override;
private:
	ga_sprite_component * _sprite;
	Uint32 _color;
};
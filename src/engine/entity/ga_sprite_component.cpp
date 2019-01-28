#include "ga_sprite_component.h"
#include "framework/ga_sim.h"
#include "ga_entity.h"
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
	check_collisions(params->_sim);
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

// rect bounds check against all the other sprites
void ga_sprite_component::check_collisions(ga_sim* sim)
{
	for (ga_entity* e : *sim->get_entities())
	{
		ga_sprite_component *s2 = e->get_component<ga_sprite_component>();
		if (s2 != nullptr && s2 != this)
		{
			if (this->_collision_mask & s2->_collision_type)
			{
				SDL_Rect collision_rect;
				bool collides = SDL_IntersectRect(&_rect, &s2->_rect, &collision_rect);
				if (collides)
				{
					sim->destroy_entity(s2->get_entity());
					//std::cout << "collision " << _name << " " << s2->_name << std::endl;
				}
			}
		}
	}

}
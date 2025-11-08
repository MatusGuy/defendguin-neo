#pragma once

#include <cog2d/input/inputmanager.hpp>

struct Entity;

struct Player
{
	cog2d::ControllerId ctrl;
};

namespace systems {
void player_construct(Entity& ent);
void player_update(Entity& ent);
}  //namespace systems

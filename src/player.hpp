#pragma once

#include <cog2d/input/inputmanager.hpp>

struct Entity;

struct Player
{
	cog2d::ControllerId ctrl;
};

namespace dgnsystem {
void player(Entity& ent);
}

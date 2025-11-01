#pragma once

#include <cog2d/input/inputmanager.hpp>

struct Entity;

struct Player
{
	cog2d::ControllerId ctrl;
};

namespace dgn {
namespace system {
void player_update(Entity& ent);
}
}  //namespace dgn

#pragma once

#include <cog2d/input/inputmanager.hpp>
#include <cog2d/ecs/entityid.hpp>
#include <cog2d/util/timer.hpp>

#include "bulletblaster.hpp"
#include "bulletrocket.hpp"

struct Entity;

enum Weapon : std::uint8_t
{
	WEAPON_BLASTER,
	WEAPON_ROCKET
};

struct Player
{
	cog2d::ControllerId ctrl;

	cog2d::Timer cooldown;
	Weapon weapon = WEAPON_BLASTER;
	std::uint8_t current_bullet;
	cog2d::EntityId bullets[2][5];
};

namespace systems {
void player_construct(Entity& ent);
void player_update(Entity& ent);
}  //namespace systems

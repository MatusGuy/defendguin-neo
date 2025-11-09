#pragma once

#include <cog2d/util/math/vector.hpp>
#include <cog2d/util/timer.hpp>

struct EnemyFighter
{
	cog2d::Timer timer;
	cog2d::Vector origin;
};

struct Entity;
namespace systems {
void enemy_fighter_construct(Entity& ent);
void enemy_fighter_init(Entity& ent);
void enemy_fighter_activate(Entity& ent);
void enemy_fighter_update(Entity& ent);
}  //namespace systems

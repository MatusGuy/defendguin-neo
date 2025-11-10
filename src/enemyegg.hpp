#pragma once

#include <cstdint>

#include <cog2d/util/timer.hpp>
#include <cog2d/ecs/entityid.hpp>

struct Entity;
struct EnemyEgg
{
	cog2d::Timer cooldown;
	cog2d::EntityId bullets[2];  // TODO: Global registry of bullets used by enemies
	std::uint8_t current_bullet = 0;
};

namespace systems {
void enemy_egg_construct(Entity& ent);
void enemy_egg_activate(Entity& ent);
void enemy_egg_update(Entity& ent);
}  //namespace systems

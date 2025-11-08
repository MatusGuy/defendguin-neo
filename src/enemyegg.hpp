#pragma once

#include <cstdint>

struct Entity;

struct EnemyEgg
{
	// std::int32_t health;
};

namespace systems {
void enemy_egg_construct(Entity& ent);
}  //namespace systems

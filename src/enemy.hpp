#pragma once

#include <cstdint>

struct Entity;

struct Enemy
{
	std::int32_t health;
};

namespace systems {
void enemy_init(Entity& ent);
}  //namespace systems

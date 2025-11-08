#pragma once

#include <cinttypes>

struct CompEnemy
{
	static std::size_t PROP_COUNT;

	std::uint16_t health;
};

struct Entity;
namespace systems {
void enemy_construct(Entity& ent);
}

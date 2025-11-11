#pragma once

#include <cinttypes>

#include <cog2d/ecs/builtins/collision/collisionsystem.hpp>

struct CompEnemy
{
	static std::size_t PROP_COUNT;

	std::uint16_t health;
};

struct Entity;
namespace systems {
void enemy_construct(Entity& ent);
cog2d::CollisionResponse enemy_collision(Entity& ent, Entity& other);
}  //namespace systems

#pragma once

#include <cinttypes>

#include <cog2d/ecs/builtins/collision/collisionsystem.hpp>

struct CompBullet
{
	int damage = 1;
};

struct Entity;
namespace systems {

void bullet_construct(Entity& ent);
void bullet_deactivate(Entity& ent);
cog2d::CollisionResponse bullet_collision(Entity& ent, Entity&);
cog2d::CollisionResponse bullet_collision_tile(Entity& ent, std::size_t);

}  //namespace systems

#pragma once

#include <cog2d/ecs/builtins/collision/collisionsystem.hpp>

struct Entity;
namespace systems {
void bullet_blaster_construct(Entity& ent);
void bullet_blaster_deactivate(Entity& ent);
cog2d::CollisionResponse bullet_blaster_collision(Entity& ent, Entity& other);
}  //namespace systems

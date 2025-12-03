#pragma once

#include <cinttypes>

struct BulletRocket
{};

struct Entity;
namespace systems {

void bullet_rocket_construct(Entity& ent);
void bullet_rocket_update(Entity& ent);
void bullet_rocket_collision(Entity& ent, Entity& other);
void bullet_rocket_collision_tile(Entity& ent, std::size_t tileidx);

}  //namespace systems

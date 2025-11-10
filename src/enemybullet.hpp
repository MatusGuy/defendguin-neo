#pragma once

struct Entity;
namespace systems {
void enemy_bullet_construct(Entity& ent);
void enemy_bullet_deactivate(Entity& ent);
}  //namespace systems

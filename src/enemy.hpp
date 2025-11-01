#pragma once

struct Entity;

struct Enemy
{
	int health;
};

namespace systems {
void enemy_init(Entity& ent);
}  //namespace systems

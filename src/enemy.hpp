#pragma once

struct Entity;

struct Enemy
{
	int health;
};

namespace dgn {
namespace system {
void enemy_init(Entity& ent);
}
}  //namespace dgn

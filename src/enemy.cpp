#include "enemy.hpp"

#include "entity.hpp"

void dgn::system::enemy_init(Entity& ent)
{
	ent.vel = {0.5f, 0};
	ent.actor.enemy.health = 10;
}

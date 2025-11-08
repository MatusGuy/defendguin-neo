#include "enemyegg.hpp"

#include "entity.hpp"
#include "constants.hpp"

void systems::enemy_egg_construct(Entity& ent)
{
	ent.type = ETYPE_ENEMY_EGG;
	systems::enemy_construct(ent);

	ent.vel = {-0.5f, 0};
	//ent.actor.enemy.health = 10;

	ent.actor.graphic.texture.color = 0xFF0000FF;
	ent.bbox.size = {25, 25};
}

#include "enemy.hpp"

#include "entity.hpp"

void systems::enemy_init(Entity& ent)
{
	ent.type = ETYPE_ENEMY;
	ent.builtins = cog2d::COMP_COLLISION | cog2d::COMP_TEXTURE;

	ent.vel = {0.5f, 0};
	ent.actor.enemy.health = 10;

	ent.actor.graphic.texture.color = 0xFF0000FF;
	ent.bbox.size = {10, 10};
}

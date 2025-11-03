#include "enemy.hpp"

#include "entity.hpp"

void systems::enemy_init(Entity& ent)
{
	ent.type = ETYPE_ENEMY;
	ent.builtins = cog2d::COMP_COLLISION | cog2d::COMP_TEXTURE | cog2d::COMP_PROPERTIES;
	ent.props.add_property(0, cog2d::PROPTYPE_INT, &ent.actor.enemy.health);

	ent.vel = {-0.5f, 0};
	//ent.actor.enemy.health = 10;

	ent.actor.graphic.texture.color = 0xFF0000FF;
	ent.bbox.size = {10, 10};
}

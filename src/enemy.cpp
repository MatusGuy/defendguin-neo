#include "enemy.hpp"

#include "entity.hpp"
#include "constants.hpp"

std::size_t CompEnemy::PROP_COUNT = 1;

void systems::enemy_construct(Entity& ent)
{
	ent.builtins |= cog2d::COMP_COLLISION | cog2d::COMP_PROPERTIES;
	ent.comps |= COMP_ENEMY;
	ent.props.add_property(0, cog2d::PROPTYPE_INT, &ent.actor.enemy.data.health);
	ent.actor.col.group = COLGROUP_ENEMIES;
}

cog2d::CollisionResponse systems::enemy_collision(Entity& ent, Entity& other)
{
	if (other.comps & COMP_BULLET) {
		cog2d::log::debug("HIT ENEMY");
		ent.actor.enemy.data.health -= other.actor.bullet.damage;
	}

	return cog2d::COLRESP_REJECT;
}

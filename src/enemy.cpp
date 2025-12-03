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
	if (other.has_comp(COMP_BULLET)) {
		ent.actor.enemy.data.health -= other.actor.bullet.damage;
		// cog2d::log::debug(cog2d::fmt::format("HIT ENEMY {} {} {} {}", (int) other.type,
		// ent.actor.enemy.data.health, other.actor.bullet.damage,
		// ent.bbox));

		if (ent.actor.enemy.data.health <= 0)
			ent.active &= ~cog2d::ACTIVE_MANUAL;
	}

	return cog2d::COLRESP_REJECT;
}

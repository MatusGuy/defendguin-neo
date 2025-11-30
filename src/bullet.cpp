#include "bullet.hpp"

#include "entity.hpp"
#include "constants.hpp"

namespace systems {

void bullet_construct(Entity& ent)
{
	ent.comps |= COMP_BULLET;
	ent.builtins |= cog2d::COMP_COLLISION;
	ent.actor.col.group = COLGROUP_BULLETS;
	ent.follow_camera = true;
	ent.active &= ~cog2d::ACTIVE_MANUAL;
}

void bullet_deactivate(Entity& ent)
{
	ent.active &= ~cog2d::ACTIVE_MANUAL;
}

cog2d::CollisionResponse bullet_collision(Entity& ent, Entity&)
{
	bullet_deactivate(ent);
	return cog2d::COLRESP_REJECT;
}

cog2d::CollisionResponse bullet_collision_tile(Entity& ent, std::size_t)
{
	bullet_deactivate(ent);
	return cog2d::COLRESP_REJECT;
}

}  //namespace systems

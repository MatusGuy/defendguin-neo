#include "bulletblaster.hpp"

#include "entity.hpp"
#include "constants.hpp"

void systems::bullet_blaster_construct(Entity& ent)
{
	ent.type = ETYPE_BULLET_BLASTER;
	ent.builtins |= cog2d::COMP_TEXTURE | cog2d::COMP_COLLISION;
	ent.active ^= cog2d::ACTIVE_MANUAL;
	ent.follow_camera = true;
	ent.actor.col.group = COLGROUP_BULLETS;

	ent.vel = {15, 0};
	ent.bbox.size = {10, 5};

	ent.actor.graphic.texture.color = 0xFF0000FF;
}

#include "bulletblaster.hpp"

#include <cog2d/assets/assetmanager.hpp>

#include "entity.hpp"
#include "constants.hpp"

void systems::bullet_blaster_construct(Entity& ent)
{
	ent.type = ETYPE_BULLET_BLASTER;
	ent.builtins |= cog2d::COMP_TEXTURE | cog2d::COMP_COLLISION;
	ent.active &= ~cog2d::ACTIVE_MANUAL;
	ent.follow_camera = true;
	ent.actor.col.group = COLGROUP_BULLETS;

	cog2d::assets::load_pixmap(0, "images/blaster.png", ent.actor.graphic.texture.texdata);
	ent.actor.graphic.texture.off.x = 26;
	ent.bbox.size = {7, 3};

	ent.vel = {15, 0};
}

void systems::bullet_blaster_deactivate(Entity& ent)
{
	ent.active &= ~cog2d::ACTIVE_MANUAL;
}

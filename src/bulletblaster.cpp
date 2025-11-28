#include "bulletblaster.hpp"

#include <cog2d/assets/assetmanager.hpp>

#include "entity.hpp"
#include "constants.hpp"

namespace systems {

void bullet_blaster_construct(Entity& ent)
{
	ent.type = ETYPE_BULLET_BLASTER;
	ent.builtins |= cog2d::COMP_TEXTURE | cog2d::COMP_COLLISION;
	ent.actor.col.group = COLGROUP_BULLETS;
	ent.follow_camera = true;
	ent.active &= ~cog2d::ACTIVE_MANUAL;

	ent.comps |= COMP_BULLET;
	ent.actor.bullet.damage = 1;

	cog2d::assets::load_pixmap(0, "images/blaster.png", ent.actor.graphic.texture.texdata);
	ent.actor.graphic.texture.off.x = 26;
	ent.bbox.size = {7, 3};

	ent.vel = {15, 0};
}

void bullet_blaster_deactivate(Entity& ent)
{
	ent.active &= ~cog2d::ACTIVE_MANUAL;
}

cog2d::CollisionResponse bullet_blaster_collision(Entity& ent, Entity& other)
{
	bullet_blaster_deactivate(ent);
	return cog2d::COLRESP_REJECT;
}

cog2d::CollisionResponse bullet_blaster_collision_tile(Entity& ent, std::size_t)
{
	bullet_blaster_deactivate(ent);
	return cog2d::COLRESP_REJECT;
}

}  //namespace systems

#include "bulletblaster.hpp"

#include <cog2d/assets/assetmanager.hpp>

#include "bullet.hpp"
#include "entity.hpp"
#include "constants.hpp"

namespace systems {

void bullet_blaster_construct(Entity& ent)
{
	ent.type = ETYPE_BULLET_BLASTER;
	ent.builtins |= cog2d::COMP_TEXTURE;
	bullet_construct(ent);

	cog2d::assets::load_pixmap(0, "images/blaster.png", ent.actor.graphic.texture.texdata);
	ent.actor.graphic.texture.off.x = 26;
	ent.bbox.size = {7, 3};

	ent.vel = {15, 0};
	ent.actor.bullet.damage = 1;
}
}  //namespace systems

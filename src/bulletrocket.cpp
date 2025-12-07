#include "bulletrocket.hpp"

#include <cog2d/assets/assetmanager.hpp>

#include "bullet.hpp"
#include "entity.hpp"

namespace systems {

void bullet_rocket_construct(Entity& ent)
{
	ent.type = ETYPE_BULLET_ROCKET;
	ent.builtins |= cog2d::COMP_TEXTURE;
	bullet_construct(ent);

	// cog2d::assets::load_pixmap(0, "images/rocket.png", ent.actor.graphic.texture.texdata);
	// ent.actor.graphic.texture.off.x = 21;
	// ent.bbox.size = {6, 5};

	// cog2d::assets::load_pixmap(0, "images/rocket2.png", ent.actor.graphic.texture.texdata);
	// ent.actor.graphic.texture.off.x = 22;
	// ent.bbox.size = {6, 5};

	// cog2d::assets::load_pixmap(0, "images/rocket3.png", ent.actor.graphic.texture.texdata);
	// ent.actor.graphic.texture.off.x = 22;
	// ent.bbox.size = {7, 5};

	// cog2d::assets::load_pixmap(0, "images/rocket4.png", ent.actor.graphic.texture.texdata);
	// ent.actor.graphic.texture.off.x = 22;
	// ent.bbox.size = {9, 7};

	// cog2d::assets::load_pixmap(0, "images/rocket5.png", ent.actor.graphic.texture.texdata);
	// ent.actor.graphic.texture.off.x = 12;
	// ent.bbox.size = {9, 9};

	cog2d::assets::load_pixmap(0, "images/rocket6.png", ent.actor.graphic.texture.texdata);
	ent.actor.graphic.texture.off.x = 12;
	ent.bbox.size = {10, 9};

	ent.vel = {7.5f, 0};
	ent.actor.bullet.damage = 3;
}

void bullet_rocket_update(Entity& ent)
{
}

void bullet_rocket_collision(Entity& ent, Entity& other)
{
}

void bullet_rocket_collision_tile(Entity& ent, std::size_t tileidx)
{
}

}  //namespace systems

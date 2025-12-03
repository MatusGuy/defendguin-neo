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

	cog2d::assets::load_pixmap(0, "images/rocket.png", ent.actor.graphic.texture.texdata);
	ent.actor.graphic.texture.off.x = 21;
	ent.bbox.size = {6, 5};

	ent.vel = {10, 0};
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

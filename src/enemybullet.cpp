#include "enemybullet.hpp"

#include <cog2d/assets/assetmanager.hpp>

#include "entity.hpp"
#include "constants.hpp"

void systems::enemy_bullet_construct(Entity& ent)
{
	ent.type = ETYPE_ENEMY_BULLET;
	ent.builtins = cog2d::COMP_COLLISION | cog2d::COMP_TEXTURE;
	ent.comps = COMP_ENEMYBULLET;

	ent.actor.col.group = COLGROUP_ENEMYBULLETS;
	ent.active &= ~cog2d::ACTIVE_MANUAL;

	cog2d::assets::load_pixmap(0, "images/enemybullet.png", ent.actor.graphic.texture.texdata);
	ent.actor.graphic.texture.off = {1, 1};
	ent.bbox.size = {4, 4};
}

void systems::enemy_bullet_deactivate(Entity& ent)
{
	ent.active &= ~cog2d::ACTIVE_MANUAL;
}

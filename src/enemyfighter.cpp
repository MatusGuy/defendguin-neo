#include "enemyfighter.hpp"

#include <cog2d/assets/assetmanager.hpp>

#include "entity.hpp"

void systems::enemy_fighter_construct(Entity& ent)
{
	ent.type = ETYPE_ENEMY_FIGTHER;
	ent.builtins |= cog2d::COMP_TEXTURE;
	systems::enemy_construct(ent);

	cog2d::assets::load_pixmap(0, "images/fighter.png", ent.actor.graphic.texture.texdata);
	ent.bbox.size = ent.actor.graphic.texture.texdata->size();

	ent.vel = {-1.f, 0.f};
}

void systems::enemy_fighter_init(Entity& ent)
{
	ent.actor.enemy.fighter.origin = ent.bbox.pos;
}

void systems::enemy_fighter_activate(Entity& ent)
{
	using namespace std::chrono_literals;
	ent.actor.enemy.fighter.timer.start(1s);
}

void systems::enemy_fighter_update(Entity& ent)
{
	ent.vel.y = std::sin(ent.actor.enemy.fighter.timer.progress() * 2.f * M_PI) * 4.f;
}

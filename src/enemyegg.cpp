#include "enemyegg.hpp"

#include "game.hpp"
#include "constants.hpp"

void systems::enemy_egg_construct(Entity& ent)
{
	ent.type = ETYPE_ENEMY_EGG;
	ent.builtins |= cog2d::COMP_TEXTURE;
	systems::enemy_construct(ent);

	ent.vel = {-0.5f, 0};
	//ent.actor.enemy.health = 10;

	ent.actor.graphic.texture.color = 0xFF00FFFF;
	ent.bbox.size = {25, 25};

	for (int i = 0; i < 2; ++i) {
		Entity& bullet = game::world.create();
		systems::enemy_bullet_construct(bullet);
		game::colsystem.m_entities.push_back(bullet.id);
		ent.actor.enemy.egg.bullets[i] = bullet.id;
	}
}

void systems::enemy_egg_activate(Entity& ent)
{
	using namespace std::chrono_literals;
	ent.actor.enemy.egg.cooldown.start(1s);
}

void enemy_egg_fire(Entity& ent)
{
	EnemyEgg& egg = ent.actor.enemy.egg;

	Entity& player = game::world[game::nearest_player(ent.bbox.middle())];
	Entity& bullet = game::world[egg.bullets[egg.current_bullet]];
	bullet.bbox.pos = ent.bbox.pos;
	bullet.vel = (player.bbox.pos - bullet.bbox.pos).normalized() * 5;
	bullet.active |= cog2d::ACTIVE_MANUAL;

	++egg.current_bullet;
	if (egg.current_bullet >= 2)
		egg.current_bullet = 0;
}

void systems::enemy_egg_update(Entity& ent)
{
	if (!ent.actor.enemy.egg.cooldown.check())
		return;

	using namespace std::chrono_literals;
	ent.actor.enemy.egg.cooldown.start(1s);

	enemy_egg_fire(ent);
}

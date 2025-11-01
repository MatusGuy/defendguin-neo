#include "game.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/ecs/ecs.hpp>

#include "entity.hpp"

namespace dgn::game {

static cog2d::Ecs<Entity> s_ecs;

void init()
{
	Entity& player = s_ecs.create();
	player.type = ETYPE_PLAYER;
	player.bbox = {{0, 0}, {10, 10}};
	player.actor.player.ctrl = 0;

	Entity& enemy = s_ecs.create();
	enemy.type = ETYPE_ENEMY;
	enemy.bbox = {{100, 100}, {10, 10}};
	system::enemy_init(enemy);
}

void draw()
{
	for (int i = 0; i < s_ecs.num_entities(); ++i) {
		Entity& ent = s_ecs[i];
		cog2d::graphics::draw_rect(ent.bbox, false, 0xFF0000FF);
	}
}

void update()
{
	for (int i = 0; i < s_ecs.num_entities(); ++i) {
		Entity& ent = s_ecs[i];

		if (ent.type == ETYPE_PLAYER)
			system::player_update(ent);

		cog2d::system::velocity(ent, ent.actor.col);
	}
}

}  //namespace dgn::game

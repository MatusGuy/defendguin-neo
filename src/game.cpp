#include "game.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/ecs/ecs.hpp>

#include "entity.hpp"

namespace game {

static cog2d::Ecs<Entity> s_ecs;

void init()
{
	Entity& player = s_ecs.create();
	systems::player_init(player);
	player.bbox.pos = {0, 0};
	player.actor.player.ctrl = 0;

	Entity& enemy = s_ecs.create();
	systems::enemy_init(enemy);
	enemy.bbox.pos = {100, 100};
}

void draw()
{
	for (int i = 0; i < s_ecs.num_entities(); ++i) {
		Entity& ent = s_ecs[i];
		if (ent.builtins & cog2d::COMP_TEXTURE)
			cog2d::systems::texture_draw(ent, ent.actor.graphic.texture);
	}
}

void update()
{
	for (int i = 0; i < s_ecs.num_entities(); ++i) {
		Entity& ent = s_ecs[i];

		if (ent.type == ETYPE_PLAYER)
			systems::player_update(ent);

		cog2d::systems::velocity_update(ent, ent.actor.col);
	}
}

}  //namespace game

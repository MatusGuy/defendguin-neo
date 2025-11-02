#include "game.hpp"

#include <cog2d/video/graphicsengine.hpp>

namespace game {

cog2d::World<Entity> world;
cog2d::TileMap tilemap;

int create_entity(std::string_view classname, cog2d::EntityBase** ent,
                  cog2d::CompProperties** props)
{
	if (classname == "Enemy") {
		Entity& e = world.create();
		systems::enemy_init(e);

		*ent = &e;
		*props = &e.actor.props;

		return 0;
	}

	if (classname == "EnemyFighter") {
		Entity& e = world.create();
		systems::enemy_init(e);

		*ent = &e;
		*props = &e.actor.props;

		return 0;
	}

	return 1;
}

void init()
{
	world.viewport.region = {{0, 0}, cog2d::graphics::logical_size()};

	tilemap.load(cog2d::File::from_asset("levels/cool.dat"), create_entity);

	Entity& player = world.create();
	systems::player_init(player);
	player.bbox.pos = {50, 50};
	player.actor.player.ctrl = 0;

	Entity& enemy = world.create();
	systems::enemy_init(enemy);
	enemy.bbox.pos = {100, 100};
}

void draw()
{
	tilemap.draw();

	for (int i = 0; i < world.num_entities; ++i) {
		Entity& ent = world[i];
		if (ent.builtins & cog2d::COMP_TEXTURE)
			cog2d::systems::texture_draw(ent, ent.actor.graphic.texture);
	}
}

void update_camera()
{
	cog2d::Vector& viewportpos = world.viewport.region.pos;
	cog2d::Vector oldpos = viewportpos;

	viewportpos.x += 1;

	world.viewport.delta = viewportpos - oldpos;
}

void update()
{
	for (int i = 0; i < world.num_entities; ++i) {
		Entity& ent = world[i];

		if (ent.type == ETYPE_PLAYER)
			systems::player_update(ent);

		cog2d::systems::velocity_update(ent, ent.actor.col);
	}

	update_camera();
}

}  //namespace game

cog2d::Viewport& cog2d::ext::viewport = game::world.viewport;

#include "game.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/ecs/builtins/collision/collisionsystem.hpp>

#include "constants.hpp"

namespace game {

cog2d::World<Entity> world;
cog2d::TileMap tilemap;
cog2d::CollisionSystem colsystem;

}  //namespace game

int create_entity(std::string_view classname, cog2d::EntityBase** ent,
                  cog2d::CompProperties** props)
{
	if (classname == "Enemy") {
		Entity& e = game::world.create();
		systems::enemy_init(e);
		game::colsystem.m_entities.push_back(e.id);

		*ent = &e;
		*props = &e.props;

		return 0;
	}

	if (classname == "EnemyFighter") {
		Entity& e = game::world.create();
		systems::enemy_init(e);
		game::colsystem.m_entities.push_back(e.id);

		*ent = &e;
		*props = &e.props;

		return 0;
	}

	return 1;
}

namespace cog2d::ext {
void entity_collision(EntityId id, EntityBase** ent, CompCollision** col)
{
	*ent = &game::world[id];
	*col = &game::world[id].actor.col;
}
}  //namespace cog2d::ext

namespace game {
void init()
{
	world.viewport.region = {{0, 0}, cog2d::graphics::logical_size()};

	colsystem.m_tilemap = &tilemap;
	colsystem.enable_interaction(COLGROUP_PLAYERS, COLGROUP_ENEMIES);

	tilemap.load(cog2d::File::from_asset("levels/cool.dat"), create_entity);

	Entity& player = world.create();
	systems::player_init(player);
	colsystem.m_entities.push_back(player.id);
	player.bbox.pos = {50, 50};
	player.actor.player.ctrl = 0;
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
	update_camera();

	for (int i = 0; i < world.num_entities; ++i) {
		Entity& ent = world[i];

		if (ent.type == ETYPE_PLAYER)
			systems::player_update(ent);

		cog2d::systems::velocity_update(ent, ent.actor.col);
	}

	colsystem.update();
}

}  //namespace game

cog2d::Viewport& cog2d::ext::viewport = game::world.viewport;

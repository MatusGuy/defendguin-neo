#include "game.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/ecs/builtins/collision/collisionsystem.hpp>
#include <cog2d/util/logger.hpp>

#include "constants.hpp"

namespace game {

cog2d::World<Entity> world;
cog2d::TileMap tilemap;
cog2d::CollisionSystem colsystem;

cog2d::EntityId players[4];
std::uint32_t player_count = 1;

cog2d::EntityId nearest_player(cog2d::Vector pos)
{
	cog2d::EntityId out = 0;
	float dist = 0;
	for (int i = 0; i < player_count; ++i) {
		cog2d::EntityId player = players[i];
		float plrdist = pos.distance(world[player].bbox.pos);
		if (out == 0 || dist > plrdist) {
			dist = plrdist;
			out = player;
		}
	}
	return out;
}

}  //namespace game

namespace cog2d::ext {
void entity_get_collision(EntityId id, EntityBase** ent, CompCollision** col)
{
	*ent = &game::world[id];
	*col = &game::world[id].actor.col;
}

CollisionResponse entity_collision(EntityBase& a_, EntityBase& b_)
{
	CollisionResponse out = COLRESP_ACCEPT;
	Entity& a = static_cast<Entity&>(a_);
	Entity& b = static_cast<Entity&>(b_);

	if (a.has_comp(COMP_ENEMY)) {
		out = ::systems::enemy_collision(a, b);
	}

	if (a.has_comp(COMP_BULLET)) {
		out = ::systems::bullet_collision(a, b);
	}

	switch (a.type) {
	// ...
	default:
		break;
	}

	return out;
}

CollisionResponse entity_collision_tile(EntityBase& ent_, std::size_t tileidx)
{
	CollisionResponse out = COLRESP_ACCEPT;
	Entity& ent = static_cast<Entity&>(ent_);

	if (ent.has_comp(COMP_BULLET)) {
		out = ::systems::bullet_collision_tile(ent, tileidx);
	}

	switch (ent.type) {
	// ...
	default:
		break;
	}

	return out;
}
}  //namespace cog2d::ext

namespace game {
int create_entity(std::string_view classname, cog2d::EntityBase*& ent,
                  cog2d::CompProperties*& props)
{
	if (classname == "EnemyEgg") {
		Entity& e = game::world.create();
		systems::enemy_egg_construct(e);
		game::colsystem.m_entities.push_back(e.id);

		ent = &e;
		props = &e.props;

		return 0;
	}

	if (classname == "EnemyFighter") {
		Entity& e = game::world.create();
		systems::enemy_fighter_construct(e);
		game::colsystem.m_entities.push_back(e.id);

		ent = &e;
		props = &e.props;

		return 0;
	}

	return 1;
}

int init_entity(cog2d::EntityBase& ent_)
{
	Entity& ent = static_cast<Entity&>(ent_);

	switch (ent.type) {
	case ETYPE_ENEMY_FIGTHER:
		systems::enemy_fighter_init(ent);
		break;

	default:
		break;
	}

	return 0;
}

void init()
{
	world.viewport.region = {{0, 0}, cog2d::graphics::logical_size()};

	colsystem.m_tilemap = &tilemap;

	colsystem.enable_interaction(COLGROUP_PLAYERS, COLGROUP_ENEMIES);
	colsystem.enable_interaction(COLGROUP_BULLETS, COLGROUP_ENEMIES);
	colsystem.enable_interaction(COLGROUP_PLAYERS, COLGROUP_ENEMYBULLETS);

	colsystem.enable_tile_interaction(COLGROUP_PLAYERS);
	colsystem.enable_tile_interaction(COLGROUP_ENEMIES);
	colsystem.enable_tile_interaction(COLGROUP_BULLETS);
	colsystem.enable_tile_interaction(COLGROUP_ENEMYBULLETS);

	tilemap.load(cog2d::File::from_asset("levels/cool.dat"), create_entity, init_entity);

	Entity& player = world.create();
	systems::player_construct(player);
	colsystem.m_entities.push_back(player.id);
	player.bbox.pos = {50, 50};
	player.actor.player.ctrl = 0;
	players[0] = player.id;
}

void draw()
{
	tilemap.draw();

	for (int i = 0; i < world.num_entities; ++i) {
		Entity& ent = world[i];

		if (!(ent.active & cog2d::ACTIVE_VIEWPORT) || !(ent.active & cog2d::ACTIVE_MANUAL))
			continue;

		if (ent.builtins & cog2d::COMP_TEXTURE)
			cog2d::systems::texture_draw(ent, ent.actor.graphic.texture);
	}
}

void activate_entity(Entity& ent)
{
	switch (ent.type) {
	case ETYPE_ENEMY_EGG:
		systems::enemy_egg_activate(ent);
		break;
	case ETYPE_ENEMY_FIGTHER:
		systems::enemy_fighter_activate(ent);
		break;
	default:
		break;
	}
}

void deactivate_entity(Entity& ent)
{
	if (ent.has_comp(COMP_BULLET)) {
		systems::bullet_deactivate(ent);
	}

	switch (ent.type) {
	case ETYPE_ENEMY_BULLET:
		systems::enemy_bullet_deactivate(ent);
		break;
	default:
		break;
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

		if (!world.update_viewport_state(ent, activate_entity, deactivate_entity))
			continue;

		if (ent.type == ETYPE_PLAYER)
			systems::player_update(ent);
		else if (ent.type == ETYPE_ENEMY_EGG)
			systems::enemy_egg_update(ent);
		else if (ent.type == ETYPE_ENEMY_FIGTHER)
			systems::enemy_fighter_update(ent);

		cog2d::systems::velocity_update(ent, ent.actor.col);
	}

	colsystem.update();
}

}  //namespace game

cog2d::Viewport& cog2d::ext::viewport = game::world.viewport;

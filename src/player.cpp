#include "player.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/assets/assetmanager.hpp>

#include "constants.hpp"
#include "game.hpp"

constexpr float SPEED = 3.f;

namespace systems {

void player_construct(Entity& ent)
{
	ent.type = ETYPE_PLAYER;
	ent.builtins = cog2d::COMP_COLLISION | cog2d::COMP_TEXTURE;
	ent.follow_camera = true;

	ent.actor.col.group = COLGROUP_PLAYERS;

	cog2d::assets::load_pixmap(0, "images/kendrick_mini.png", ent.actor.graphic.texture.texdata);
	ent.bbox.size = ent.actor.graphic.texture.texdata->size();

	// for (int i = 0; i < 5; ++i) {
	// Entity& bullet = game::world.create();
	// systems::bullet_blaster_construct(bullet);
	// game::colsystem.m_entities.push_back(bullet.id);
	// ent.actor.player.bullets[WEAPON_BLASTER][i] = bullet.id;
	// }

	for (int i = 0; i < 5; ++i) {
		Entity& bullet = game::world.create();
		systems::bullet_rocket_construct(bullet);
		game::colsystem.m_entities.push_back(bullet.id);
		ent.actor.player.bullets[WEAPON_ROCKET][i] = bullet.id;
	}

	ent.actor.player.weapon = WEAPON_ROCKET;
}

void player_fire(Entity& ent)
{
	Player& player = ent.actor.player;
	switch (player.weapon) {
	default: {
		Entity& bullet = game::world[player.bullets[player.weapon][player.current_bullet]];
		bullet.active |= cog2d::ACTIVE_MANUAL;
		bullet.bbox.pos.x = ent.bbox.get_right();
		bullet.bbox.pos.y = (ent.bbox.pos.y + ent.bbox.size.y / 2) - (bullet.bbox.size.y / 2);
		bullet.vel.x *= +1;
		// game::activate_entity(bullet);

		++player.current_bullet;
		if (player.current_bullet >= 5)
			player.current_bullet = 0;

		using namespace std::chrono_literals;
		player.cooldown.start(100ms);

		break;
	}
	}
}

void player_update(Entity& ent)
{
	Player& player = ent.actor.player;
	ent.vel = {0, 0};
	// float mult = cog2d::input::hold(player.ctrl, InputActions::FIRE) ? 2.f : 1.f;
	const float mult = 1.f;
	const float movement = SPEED * mult;
	const cog2d::Rect viewportrect = game::world.viewport.region;

	if (cog2d::input::hold(player.ctrl, InputActions::DOWN) &&
	    ent.bbox.get_bottom() + movement <= viewportrect.get_bottom()) {
		ent.vel.y = movement;

	} else if (cog2d::input::hold(player.ctrl, InputActions::UP) &&
	           ent.bbox.get_top() - movement >= viewportrect.get_top()) {
		ent.vel.y = -movement;
	}

	if (cog2d::input::hold(player.ctrl, InputActions::RIGHT) &&
	    ent.bbox.get_right() + movement <= viewportrect.get_right()) {
		ent.vel.x = movement;

	} else if (cog2d::input::hold(player.ctrl, InputActions::LEFT) &&
	           ent.bbox.get_left() - movement >= viewportrect.get_left()) {
		ent.vel.x = -movement;
	}

	if (cog2d::input::hold(player.ctrl, InputActions::FIRE) && !player.cooldown.started()) {
		player_fire(ent);
	}

	player.cooldown.check();
}

}  //namespace systems

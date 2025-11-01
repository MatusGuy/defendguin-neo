#include "player.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/assets/assetmanager.hpp>

#include "constants.hpp"
#include "entity.hpp"

constexpr float SPEED = 3.f;

namespace systems {

void player_init(Entity& ent)
{
	ent.type = ETYPE_PLAYER;
	ent.builtins = cog2d::COMP_COLLISION | cog2d::COMP_TEXTURE;

	ent.actor.graphic.texture
	    .texdata = cog2d::Texture::from_pixmap(cog2d::File::from_asset("images/kendrick.png"));
	ent.bbox.size = ent.actor.graphic.texture.texdata->size();
}

void player_update(Entity& ent)
{
	Player& player = ent.actor.player;
	ent.vel = {0, 0};
	float mult = cog2d::input::hold(player.ctrl, InputActions::FIRE) ? 2.f : 1.f;
	//const float mult = 1.f;
	const float movement = SPEED * mult;
	const cog2d::Rect_t<int> viewportrect = {{0, 0}, cog2d::graphics::get_logical_size()};

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
}

}  //namespace systems

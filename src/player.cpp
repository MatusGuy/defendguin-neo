#include "player.hpp"

#include <algorithm>

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/scene/actormanager.hpp>
#include <cog2d/util/logger.hpp>
#include <cog2d/scene/viewport.hpp>
#include <cog2d/audio/musicplayer.hpp>

#include "weaponpeashooter.hpp"
#include "weaponrocket.hpp"

constexpr float SPEED = 3.f;

Player::Player()
    : cog2d::Actor(),
      m_controller(0),
      m_current_weapon(nullptr),
      m_weapons(),
      m_texture()
{
}

void Player::add_components()
{
	add_component<cog2d::ActorComps::Geometry>();
	add_component<cog2d::ActorComps::Velocity>();
	add_component<cog2d::ActorComps::Collision>();
}

void Player::init()
{
	COG2D_USE_ACTORMANAGER;

	follow_camera() = true;
	col().group = COLGROUP_PLAYERS;

	m_texture = cog2d::assets::pixmaps.load_file("images/kendrick.png");
	bbox() = {{0, 0}, m_texture->size()};

	auto weapon = std::make_pair<Weapon::Type,
	                             std::unique_ptr<Weapon>>(static_cast<Weapon::Type>(0), nullptr);
	weapon.first = WeaponPeashooter::type_s();
	weapon.second = std::make_unique<WeaponPeashooter>(this);

	/*
	auto weapon = std::make_pair<Weapon::Type,
								 std::unique_ptr<Weapon>>(static_cast<Weapon::Type>(0), nullptr);
	weapon.first = WeaponRocket::type_s();
	weapon.second = std::make_unique<WeaponRocket>(this);
	*/

	/*
	auto weapon = std::make_pair<Weapon::Type,
	                             std::unique_ptr<Weapon>>(static_cast<Weapon::Type>(0), nullptr);
	weapon.first = WeaponRocket2::type_s();
	weapon.second = std::make_unique<WeaponRocket2>(this);
	*/

	m_current_weapon = weapon.second.get();
	m_weapons.insert(std::move(weapon));

	m_current_weapon->init();
}

void Player::update()
{
	COG2D_USE_VIEWPORT;

	vel() = {0, 0};

	//float mult = cog2d::input::hold(m_controller, InputActions::FIRE) ? 2.f : 1.f;
	const float mult = 1.f;
	const float movement = SPEED * mult;
	const cog2d::Rect viewportrect = viewport.get_scene_rect();

	if (cog2d::input::hold(m_controller, InputActions::DOWN) &&
	    bbox().get_bottom() + movement <= viewportrect.get_bottom()) {
		vel().y = movement;

	} else if (cog2d::input::hold(m_controller, InputActions::UP) &&
	           bbox().get_top() - movement >= viewportrect.get_top()) {
		vel().y = -movement;
	}

	if (cog2d::input::hold(m_controller, InputActions::RIGHT) &&
	    bbox().get_right() + movement <= viewportrect.get_right()) {
		vel().x = movement;

	} else if (cog2d::input::hold(m_controller, InputActions::LEFT) &&
	           bbox().get_left() - movement >= viewportrect.get_left()) {
		vel().x = -movement;
	}

	if (cog2d::input::hold(m_controller, InputActions::FIRE)) {
		m_current_weapon->fire();
		cog2d::audio::music.queue_section(1);
	}

	m_current_weapon->update();

	cog2d::Actor::update();
	//cog2d::log::debug(std::format("p: {}, {}, {}, {}", m_bbox.get_left(), m_bbox.get_top(),
	//m_movement.x, m_movement.y));
}

void Player::draw()
{
	COG2D_USE_ACTORMANAGER;

	cog2d::graphics::draw_texture(m_texture.get(), viewport_pos());
}

cog2d::CollisionSystem::Response Player::collision(cog2d::Actor* other)
{
	if (other->col().group == COLGROUP_ENEMYBULLETS)
		cog2d::log::debug("HIT");

	return cog2d::CollisionSystem::COLRESP_ACCEPT;
}

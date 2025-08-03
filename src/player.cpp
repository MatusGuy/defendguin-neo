#include "player.hpp"

#include <algorithm>

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/scene/actormanager.hpp>
#include <cog2d/util/logger.hpp>
#include <cog2d/scene/viewport.hpp>

#include "weaponpeashooter.hpp"
#include "weaponrocket.hpp"

constexpr float SPEED = 2.f;

Player::Player()
    : cog2d::Actor(),
      m_controller(nullptr),
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
	COG2D_USE_ASSETMANAGER;

	follow_camera() = true;
	col().group = COLGROUP_PLAYERS;

	m_texture = assetmanager.pixmaps.load_file("images/kendrick.png");
	bbox() = {{0, 0}, m_texture->get_size()};

	/*
	auto peashooter = std::make_pair<Weapon::Type,
	                                 std::unique_ptr<Weapon>>(static_cast<Weapon::Type>(0),
	                                                          nullptr);
	peashooter.first = WeaponPeashooter::type_s();
	peashooter.second = std::make_unique<WeaponPeashooter>(this);
	*/

	auto rocket = std::make_pair<Weapon::Type,
	                             std::unique_ptr<Weapon>>(static_cast<Weapon::Type>(0), nullptr);
	rocket.first = WeaponRocket::type_s();
	rocket.second = std::make_unique<WeaponRocket>(this);

	m_current_weapon = rocket.second.get();
	m_weapons.insert(std::move(rocket));

	m_current_weapon->init();
}

void Player::update()
{
	COG2D_USE_VIEWPORT;

	vel() = {0, 0};

	//float mult = m_controller->held(InputActions::FIRE) ? 2.f : 1.f;
	const float mult = 1.f;
	const float movement = SPEED * mult;
	const cog2d::Rect viewportrect = viewport.get_scene_rect();

	if (m_controller->held(InputActions::DOWN) &&
	    bbox().get_bottom() + movement <= viewportrect.get_bottom()) {
		vel().y = movement;

	} else if (m_controller->held(InputActions::UP) &&
	           bbox().get_top() - movement >= viewportrect.get_top()) {
		vel().y = -movement;
	}

	if (m_controller->held(InputActions::RIGHT) &&
	    bbox().get_right() + movement <= viewportrect.get_right()) {
		vel().x = movement;

	} else if (m_controller->held(InputActions::LEFT) &&
	           bbox().get_left() - movement >= viewportrect.get_left()) {
		vel().x = -movement;
	}

	if (m_controller->held(InputActions::FIRE)) {
		m_current_weapon->fire();
	}

	m_current_weapon->update();

	cog2d::Actor::update();
	//COG2D_LOG_DEBUG(std::format("p: {}, {}, {}, {}", m_bbox.get_left(), m_bbox.get_top(),
	//m_movement.x, m_movement.y));
}

void Player::draw()
{
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_texture(m_texture.get(), viewport_pos());
}

cog2d::CollisionSystem::Response Player::collision(cog2d::Actor* other)
{
	if (other->col().group == COLGROUP_ENEMYBULLETS)
		COG2D_LOG_DEBUG("HIT");

	return cog2d::CollisionSystem::COLRESP_ACCEPT;
}

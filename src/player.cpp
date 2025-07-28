#include "player.hpp"

#include <algorithm>

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/scene/actormanager.hpp>
#include <cog2d/util/logger.hpp>
#include <cog2d/scene/viewport.hpp>

constexpr float SPEED = 2.f;

Player::Player()
    : cog2d::Actor(),
      m_controller(nullptr),
      m_cooldown(0),
      m_current_bullet(0),
      m_bullets(),
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

	std::pair<Bullet::Type, std::list<Bullet*>> pair;
	auto& bullets = pair.second;
	pair.first = 0;
	bullets.resize(2);

	std::list<Bullet*>::iterator iter;
	for (iter = bullets.begin(); iter != bullets.end(); iter++) {
		auto bullet = std::make_unique<Bullet>(this);
		*iter = bullet.get();
		actormanager.add(std::move(bullet));
	}
	m_bullets.insert(pair);
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

	// TODO: proper bullet types
	std::list<Bullet*>& bullets = m_bullets[0];
	Bullet* bullet = bullets.front();
	if (m_controller->held(InputActions::FIRE) && m_cooldown <= 0 && !bullet->is_active()) {
		m_cooldown = 5;

		bullet->activate({bbox().pos.x + bbox().size.x, bbox().pos.y});
		bullets.splice(bullets.end(), bullets, bullets.begin());
	}

	m_cooldown--;

	cog2d::Actor::update();
	//COG2D_LOG_DEBUG(std::format("p: {}, {}, {}, {}", m_bbox.get_left(), m_bbox.get_top(),
	//m_movement.x, m_movement.y));
}

void Player::draw()
{
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_texture(m_texture.get(), viewport_pos());
}

void Player::notify_bullet_deactivate(Bullet* bullet)
{
	std::list<Bullet*>& bullets = m_bullets[0];
	auto i = std::find(bullets.begin(), bullets.end(), bullet);
	if (i == bullets.end())
		return;

	bullets.splice(bullets.begin(), bullets, i);
}

void Player::next_bullet()
{
	if (m_current_bullet + 1 >= m_bullets[0].size())
		m_current_bullet = 0;
	else
		m_current_bullet++;
}

#include "bullet.hpp"

#include "player.hpp"

#include <cog2d/util/logger.hpp>

Bullet::Bullet(Player* parent)
    : cog2d::Actor(),
      m_parent(parent),
      m_active(false)
{
	m_group = COLGROUP_BULLETS;
	m_bbox = {{0, 0}, {10, 5}};
}

void Bullet::activate(cog2d::Vector pos)
{
	m_bbox.pos = pos;
	m_active = true;
	m_vel.x = 15.f;
}

void Bullet::deactivate()
{
	m_active = false;
	m_vel.x = 0.f;
	m_parent->notify_bullet_deactivate(this);
}

void Bullet::update() {
	COG2D_USE_GRAPHICSENGINE;

	if (m_bbox.pos.x + m_bbox.size.x >= static_cast<float>(graphicsengine.get_logical_size().x))
	{
		deactivate();
	}

	cog2d::Actor::update();
	//COG2D_LOG_DEBUG(std::format("b: {}, {}, {}, {}", m_bbox.get_left(), m_bbox.get_top(), m_movement.x, m_movement.y));
}

void Bullet::draw() {
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_rect(m_bbox, false, cog2d::Color(is_active() ? 0xFF0000FF : 0xFF00FF00));
}

cog2d::CollisionSystem::Response Bullet::collision(cog2d::CollisionBody* other)
{
	deactivate();
	return cog2d::CollisionSystem::COLRESP_REJECT;
}

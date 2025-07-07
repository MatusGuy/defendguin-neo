#include "bullet.hpp"

#include "player.hpp"

#include <cog2d/util/logger.hpp>

Bullet::Bullet(Player* parent)
    : cog2d::Actor(false),
      m_parent(parent)
{
}

void Bullet::add_components()
{
	add_component<cog2d::ActorComps::Geometry>();
	add_component<cog2d::ActorComps::Velocity>();
	add_component<cog2d::ActorComps::Collision>();
}

void Bullet::init()
{
	col().group = COLGROUP_BULLETS;
	bbox() = {{0, 0}, {10, 5}};
}

void Bullet::activate(cog2d::Vector pos)
{
	bbox().pos = pos;
	vel().x = 15.f;
	set_active(true);
}

void Bullet::deactivate()
{
	vel().x = 0.f;
	set_active(false);
	m_parent->notify_bullet_deactivate(this);
}

void Bullet::update() {
	COG2D_USE_GRAPHICSENGINE;

	if (bbox().pos.x + bbox().size.x >= static_cast<float>(graphicsengine.get_logical_size().x)) {
		deactivate();
	}

	cog2d::Actor::update();
	//COG2D_LOG_DEBUG(std::format("b: {}, {}, {}, {}", m_bbox.get_left(), m_bbox.get_top(), m_movement.x, m_movement.y));
}

void Bullet::draw() {
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_rect(bbox(), false, cog2d::Color(is_active() ? 0xFF0000FF : 0xFF00FFFF));
}

cog2d::CollisionSystem::Response Bullet::collision(cog2d::Actor* other)
{
	deactivate();
	return cog2d::CollisionSystem::COLRESP_REJECT;
}

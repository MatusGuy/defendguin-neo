#include "enemy.hpp"

#include <cog2d/video/graphicsengine.hpp>

Enemy::Enemy()
    : cog2d::Actor(),
      m_health(10)
{
}

void Enemy::add_components()
{
	add_component<cog2d::ActorComps::Geometry>();
	add_component<cog2d::ActorComps::Velocity>();
	add_component<cog2d::ActorComps::Collision>();
}

void Enemy::init()
{
	col().group = COLGROUP_ENEMIES;
	bbox() = {0, 0, 15, 15};
}

void Enemy::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect({viewport_pos(), bbox().size}, false, 0xFF00FFFF);
}

void Enemy::update()
{
	if (m_health <= 0)
		set_active(false);
}

cog2d::CollisionSystem::Response Enemy::collision(cog2d::Actor* other)
{
	if (other->col().group == COLGROUP_BULLETS) {
		m_health--;
		return cog2d::CollisionSystem::COLRESP_REJECT;
	}

	return cog2d::Actor::collision(other);
}

cog2d::PropertyRefs Enemy::properties()
{
	cog2d::PropertyRefs out = cog2d::Actor::properties();

	out.push_back(&m_health);

	return out;
}

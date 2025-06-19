#include "enemy.hpp"

#include <cog2d/video/graphicsengine.hpp>

Enemy::Enemy()
    : cog2d::Actor()
{
	m_group = COLGROUP_ENEMIES;
	m_health = 10;
	m_bbox = {0, 0, 15, 15};
}

void Enemy::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect(m_bbox, false, 0xFFFF00FF);
}

void Enemy::update()
{
	if (m_health <= 0)
		set_active(false);
}

cog2d::CollisionSystem::Response Enemy::collision(CollisionBody* other)
{
	if (other->m_group == COLGROUP_BULLETS)
	{
		m_health--;
		return cog2d::CollisionSystem::COLRESP_REJECT;
	}

	return cog2d::CollisionBody::collision(other);
}

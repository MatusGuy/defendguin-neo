#include "enemy.hpp"

#include "graphicsengine.hpp"

Enemy::Enemy():
	Actor()
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

bool Enemy::is_active()
{
	return m_health > 0;
}

CollisionSystem::Response
Enemy::collision(CollisionBody* other)
{
	if (other->m_group == COLGROUP_BULLETS)
	{
		m_health--;
		return CollisionSystem::COLRESP_REJECT;
	}

	return CollisionBody::collision(other);
}

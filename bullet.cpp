#include "bullet.hpp"

Bullet::Bullet(Dir dir):
	Actor()
{
	m_bbox = {{0, 0}, {10, 5}};

	m_vel = {dir == Dir::RIGHT ? 7 : -7, 0};
}

void Bullet::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect(m_bbox, true, 0x00FFFFFF);
}

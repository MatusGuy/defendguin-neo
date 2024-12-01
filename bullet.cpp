#include "bullet.hpp"

#include "player.hpp"

#include <logger.hpp>

Bullet::Bullet(Player* parent):
	Actor(),
	m_parent(parent),
	m_active(false)
{
	m_bbox = {{0, 0}, {10, 5}};
}

void Bullet::activate(Vector pos)
{
	m_bbox.pos = pos;
	m_active = true;
	m_vel.x = 20.f;
}

void Bullet::deactivate()
{
	m_active = false;
	m_vel.x = 0.f;
	m_parent->notify_bullet_deactivate(this);
}

void Bullet::update() {
	COG2D_USE_GRAPHICSENGINE;

	// TODO: Get size function (lmao)
	int w = -1;
	SDL_GetWindowSize(graphicsengine.get_window(), &w, nullptr);

	if (m_bbox.pos.x + m_bbox.size.x >= static_cast<float>(w))
	{
		deactivate();
	}

	Actor::update();
}

void Bullet::draw() {
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_rect(m_bbox, true, Color(is_active() ? 0xFF0000FF : 0x00FF00FF));
}

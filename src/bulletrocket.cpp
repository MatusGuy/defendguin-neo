// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#include "bulletrocket.hpp"

BulletRocket::BulletRocket(Weapon* parent)
    : Bullet(parent),
      m_state(State::IDLE)
{
}

void BulletRocket::activate(cog2d::Vector pos)
{
	//Bullet::activate(pos);
	bbox().pos = pos;
	vel().x = 7.f;
	set_active(true);
	m_timer.start(250);
}

void BulletRocket::deactivate()
{
	Bullet::deactivate();
	idle();
	m_timer.stop();
}

cog2d::CollisionSystem::Response BulletRocket::collision(cog2d::Actor* other)
{
	explode();
	return cog2d::CollisionSystem::COLRESP_REJECT;
}

void BulletRocket::idle()
{
	m_state = State::IDLE;
	bbox().size = {13, 8};
}

void BulletRocket::explode()
{
	m_state = State::EXPLODING;
	vel().x = 0.f;
	bbox() = {bbox().middle() - cog2d::Vector{20, 20}, {40, 40}};
	m_timer.start(500);
}

void BulletRocket::update()
{
	switch (m_state) {
	case State::IDLE:
		if (m_timer.check())
			explode();

		break;

	case State::EXPLODING:
		if (m_timer.check())
			deactivate();

		break;
	}

	Bullet::update();
}

void BulletRocket::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect({viewport_pos(), bbox().size}, false, 0xE56B1AFF);
}

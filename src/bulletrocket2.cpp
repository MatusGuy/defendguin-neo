// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#include "bulletrocket2.hpp"

#include <random>

BulletRocket2::BulletRocket2(Weapon* parent)
    : Bullet(parent),
      m_state(State::IDLE)
{
}

void BulletRocket2::add_components()
{
	Bullet::add_components();
	add_component<cog2d::ActorComps::Gravity>();
}

void BulletRocket2::init()
{
	Bullet::init();
	idle();
	grav() = 0;
}

void BulletRocket2::activate(cog2d::Vector pos)
{
	//Bullet::activate(pos);
	bbox().pos = pos;
	vel().x = 0.f;
	accel().x = 35.f;

	// TODO: cog2d random function
	auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
	m_oscillate_down = gen() == 1 ? true : false;

	set_active(true);
	m_timer.start(500ms);
}

void BulletRocket2::deactivate()
{
	Bullet::deactivate();
	accel().x = 0;
	idle();
	m_timer.stop();
}

cog2d::CollisionSystem::Response BulletRocket2::collision(cog2d::Actor* other)
{
	explode();
	return cog2d::CollisionSystem::COLRESP_REJECT;
}

void BulletRocket2::idle()
{
	m_state = State::IDLE;
	bbox().size = {13, 8};
}

void BulletRocket2::explode()
{
	m_state = State::EXPLODING;
	vel().x = 0.f;
	vel().y = 0.f;
	accel().x = 0.f;
	bbox() = {bbox().middle() - cog2d::Vector{20, 20}, {40, 40}};
	m_timer.start(500ms);
}

void BulletRocket2::update()
{
	switch (m_state) {
	case State::IDLE:
		vel().y = (m_oscillate_down ? 1 : -1) * std::sin(m_timer.get_progress() * 2 * M_PI) / 2;

		break;

	case State::EXPLODING:
		if (m_timer.check())
			deactivate();

		break;
	}

	Bullet::update();
	vel().x = std::min(vel().x, 8.f);
}

void BulletRocket2::draw()
{
	cog2d::graphics::draw_rect({viewport_pos(), bbox().size}, false, 0xE56B1AFF);
}

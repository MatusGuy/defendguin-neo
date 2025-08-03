// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include <cog2d/util/timer.hpp>

#include "bullet.hpp"

class BulletRocket2 : public Bullet
{
	COG2D_ACTOR(BulletRocket)

public:
	enum class State
	{
	    IDLE,
	    EXPLODING
    };

public:
	BulletRocket2(Weapon* parent);

	void add_components() override;
	void init() override;
	void update() override;
	void draw() override;
	void activate(cog2d::Vector pos) override;
	void deactivate() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

	void idle();
	void explode();

private:
	State m_state;
	cog2d::Timer m_timer;
};

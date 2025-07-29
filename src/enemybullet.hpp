#pragma once

#include <cog2d/scene/actor.hpp>

class Enemy;

class EnemyBullet : public cog2d::Actor
{
public:
	Enemy* m_parent;

public:
	EnemyBullet(Enemy* parent);

	void init() override;

	void activate(cog2d::Vector pos, cog2d::Vector dir);
	void deactivate();

	void draw() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

	void add_components() override;
};

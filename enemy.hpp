#ifndef ENEMY_H
#define ENEMY_H

#include <cog2d/scene/actor.hpp>

#include "constants.hpp"

class Enemy : public cog2d::Actor
{
public:
	int m_health;

public:
	Enemy();

	void init() override;

	void draw() override;
	void update() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

protected:
	void add_components() override;
};

#endif // ENEMY_H

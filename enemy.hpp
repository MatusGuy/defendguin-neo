#ifndef ENEMY_H
#define ENEMY_H

#include <cog2d/scene/actor.hpp>

#include "constants.hpp"

class Enemy : public cog2d::Actor
{
public:
	std::uint16_t m_health;

public:
	Enemy();

	void draw() override;
	bool is_active() override;
	cog2d::CollisionSystem::Response collision(cog2d::CollisionBody* other) override;
};

#endif // ENEMY_H

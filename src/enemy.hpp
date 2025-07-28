#ifndef ENEMY_H
#define ENEMY_H

#include <cog2d/scene/actor.hpp>

#include "constants.hpp"

class Enemy : public cog2d::Actor
{
	COG2D_ACTOR(Enemy)

public:
	std::int32_t m_health;

public:
	Enemy();

	void init() override;

	void draw() override;
	void update() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

	cog2d::PropertyRefs properties() override;

protected:
	void add_components() override;
};

#endif  // ENEMY_H

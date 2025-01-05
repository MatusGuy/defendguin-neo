#ifndef ENEMY_H
#define ENEMY_H

#include <actor.hpp>

#include "constants.hpp"

class Enemy : public Actor
{
public:
	std::uint16_t m_health;

public:
	Enemy();

	void draw() override;
	bool is_active() override;
	CollisionSystem::Response collision(CollisionBody* other) override;
};

#endif // ENEMY_H

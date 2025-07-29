#ifndef ENEMY_H
#define ENEMY_H

#include <forward_list>

#include <cog2d/scene/actor.hpp>
#include <cog2d/util/timer.hpp>

#include "enemybullet.hpp"
#include "constants.hpp"

class Enemy : public cog2d::Actor
{
	COG2D_ACTOR(Enemy)

public:
	std::int32_t m_health;
	std::forward_list<EnemyBullet*> m_bullets;
	cog2d::Timer m_timer;

public:
	Enemy();

	void init() override;

	void draw() override;
	void update() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

	cog2d::PropertyRefs properties() override;

	void notify_bullet_deactivate();

protected:
	void add_components() override;

	void fire();
};

#endif  // ENEMY_H

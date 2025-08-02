#ifndef BULLET_H
#define BULLET_H

#include <cog2d/assets/assetmanager.hpp>
#include <cog2d/scene/actor.hpp>

#include "constants.hpp"

class Weapon;

class Bullet : public cog2d::Actor
{
	COG2D_ACTOR(Bullet)

public:
	Weapon* m_parent;

public:
	Bullet(Weapon* parent);

	void init() override;

	void activate(cog2d::Vector pos);
	void deactivate();

	void update() override;
	void draw() override;

	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

protected:
	void add_components() override;
};

#endif  // BULLET_H

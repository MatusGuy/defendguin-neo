#ifndef BULLET_H
#define BULLET_H

#include <cog2d/assets/assetmanager.hpp>
#include <cog2d/scene/actor.hpp>

#include "constants.hpp"

class Player;

class Bullet : public cog2d::Actor
{
	COG2D_ACTOR(Bullet)

public:
	Player* m_parent;

public:
	Bullet(Player* parent);

	void init() override;

	void activate(cog2d::Vector pos);
	void deactivate();

	void update() override;
	void draw() override;

	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

	using Type = uint16_t;
	virtual Type get_type() { return 0; }

protected:
	void add_components() override;
};

#endif  // BULLET_H

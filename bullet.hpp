#ifndef BULLET_H
#define BULLET_H

#include <cog2d/scene/actor.hpp>
#include <cog2d/video/graphicsengine.hpp>

#include "constants.hpp"

class Player;

class Bullet : public cog2d::Actor
{
public:
	Player* m_parent;
	bool m_active;

public:
	Bullet(Player* parent);

	void activate(cog2d::Vector pos);
	void deactivate();

	void update() override;
	void draw() override;
	bool is_active() override { return m_active; }

	cog2d::CollisionSystem::Response collision(cog2d::CollisionBody* other) override;

	using Type = uint16_t;
	virtual Type get_type() { return 0; }
};

#endif // BULLET_H

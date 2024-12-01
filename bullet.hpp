#ifndef BULLET_H
#define BULLET_H

#include <actor.hpp>
#include <graphicsengine.hpp>

#include "constants.hpp"

class Player;

class Bullet : public Actor
{
public:
	Player* m_parent;
	bool m_active;

public:
	Bullet(Player* parent);

	void activate(Vector pos);
	void deactivate();

	void update() override;
	void draw() override;
	bool is_active() override { return m_active; }

	using Type = uint16_t;
	virtual Type get_type() { return 0; }
};

#endif // BULLET_H

#ifndef BULLET_H
#define BULLET_H

#include <actor.hpp>
#include <graphicsengine.hpp>

#include "constants.hpp"

class Bullet : public Actor
{
public:
	Bullet(Dir dir);

	void draw() override;
};

#endif // BULLET_H

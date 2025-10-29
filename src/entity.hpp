#pragma once

#include <cog2d/ecs/entity.hpp>

struct Entity : public cog2d::EntityBase
{
	union
	{
		struct
		{
			cog2d::CompCollision col;
			cog2d::CompGravity grav;
		} actor;
	};
};

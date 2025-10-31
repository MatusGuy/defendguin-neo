#pragma once

#include <cog2d/ecs/entity.hpp>
#include <cog2d/ecs/builtins.hpp>

#include "player.hpp"

struct Entity : public cog2d::EntityBase
{
	union
	{
		struct
		{
			cog2d::CompCollision col;
			cog2d::CompGravity grav;

			union
			{
				Player player;
			};
		} actor;
	};
};

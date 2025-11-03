#pragma once

#include <cog2d/ecs/entitybase.hpp>
#include <cog2d/ecs/builtins.hpp>

#include "player.hpp"
#include "enemy.hpp"

enum EntityType : std::uint16_t
{
	ETYPE_MAIN_TYPE_MASK = 0b1,
	ETYPE_MAIN_TYPE_SIZE = 1,

	ETYPE_ACTOR = 0 & ETYPE_MAIN_TYPE_MASK,
	ETYPE_PLAYER = ETYPE_ACTOR | (1 << ETYPE_MAIN_TYPE_SIZE),
	ETYPE_ENEMY = ETYPE_ACTOR | (2 << ETYPE_MAIN_TYPE_SIZE),

	ETYPE_TRIGGER = 1 & ETYPE_MAIN_TYPE_MASK
};

struct Actor
{
	cog2d::CompCollision col;
	cog2d::CompGravity grav;
	cog2d::CompGraphic graphic;

	union
	{
		Player player;
		Enemy enemy;
	};
};

struct Entity : public cog2d::EntityBase
{
	EntityType type;

	cog2d::CompProperties props;

	union
	{
		Actor actor;
	};
};

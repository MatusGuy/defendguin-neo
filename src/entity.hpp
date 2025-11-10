#pragma once

#include <cog2d/ecs/entitybase.hpp>
#include <cog2d/ecs/builtins.hpp>

#include "player.hpp"
#include "enemy.hpp"
#include "enemyegg.hpp"
#include "enemyfighter.hpp"
#include "enemybullet.hpp"

enum EntityType : std::uint16_t
{
	ETYPE_PLAYER,

	ETYPE_BULLET_BLASTER,
	ETYPE_BULLET_ROCKET,

	ETYPE_ENEMY_EGG,
	ETYPE_ENEMY_FIGTHER,

	ETYPE_ENEMY_BULLET,
};

enum Component : std::uint32_t
{
	COMP_ACTOR = (1 << 0),
	COMP_ENEMY = (1 << 1) | COMP_ACTOR,
	COMP_BULLET = (1 << 2) | COMP_ACTOR,
	COMP_ENEMYBULLET = (1 << 3) | COMP_ACTOR,
};

struct Enemy
{
	CompEnemy data;

	union
	{
		EnemyEgg egg;
		EnemyFighter fighter;
	};
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
	std::uint32_t comps = 0;

	cog2d::CompProperties props;

	union
	{
		Actor actor;
	};
};

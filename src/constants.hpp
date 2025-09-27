#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cinttypes>

#include "cog2d/util/timing.hpp"
using namespace std::chrono_literals;

#define COG2D_ACTOR_TYPES
namespace cog2d {
enum ActorType : std::uint16_t
{
	Player = 1,
	Bullet = 2,
	BulletRocket = 3,
	Enemy = 4,
	EnemyBullet = 5,
	EnemyFighter = 6
};
}

enum InputActions : std::uint8_t
{
	DOWN,
	UP,
	RIGHT,
	LEFT,
	FIRE
};

enum CollisionGroups : std::uint8_t
{
	COLGROUP_PLAYERS,
	COLGROUP_BULLETS,
	COLGROUP_ENEMIES,
	COLGROUP_ENEMYBULLETS,
};

#endif  // CONSTANTS_HPP

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cinttypes>

#define COG2D_ACTOR_TYPES
namespace cog2d {
enum ActorType : std::uint16_t
{
	Player = 1,
	Bullet = 2,
	Enemy = 3,
	EnemyBullet = 4
};
}

enum InputActions : std::uint8_t
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
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

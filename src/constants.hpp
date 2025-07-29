#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cinttypes>

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

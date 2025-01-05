#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cinttypes>

enum InputActions : uint8_t {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FIRE
};

enum CollisionGroups : uint8_t {
	COLGROUP_PLAYERS,
	COLGROUP_BULLETS,
	COLGROUP_ENEMIES,
};

#endif // CONSTANTS_HPP

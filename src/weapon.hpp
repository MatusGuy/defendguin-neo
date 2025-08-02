#pragma once

#include <cog2d/util/math/vector.hpp>

#define DGN_WEAPON(clname)              \
public:                                 \
	static Weapon::Type type_s()        \
    {                                   \
	    return Weapon::WEAPON_##clname; \
	}                                   \
	Weapon::Type type() override        \
    {                                   \
	    return type_s();                \
	}

class Player;

class Weapon
{
public:
	enum Type : std::uint8_t
	{
		WEAPON_Peashooter,
		WEAPON_Rocket,
		WEAPON_Chaser,
		WEAPON_Blade,
		WEAPON_Thunder
	};

public:
	Player* m_player;

public:
	Weapon(Player* player);

	virtual Type type() = 0;
	virtual void init() = 0;
	virtual void fire() = 0;
	virtual void notify_bullet_deactivate(void* bullet) {}
	virtual void update() {}
	//virtual void draw() {}
};

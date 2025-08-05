// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include "weaponbullet.hpp"

DGN_WEAPON_BULLET(Peashooter, Bullet, 2, std::chrono::milliseconds, 75);
class WeaponPeashooter : public WeaponPeashooter_t
{
	DGN_WEAPON(Peashooter)

public:
	WeaponPeashooter(Player* player)
	    : WeaponPeashooter_t(player)
	{
	}
};

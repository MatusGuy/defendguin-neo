// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include "weaponbullet.hpp"
#include "bulletrocket.hpp"

DGN_WEAPON_BULLET(Rocket, BulletRocket, 2, 500);
class WeaponRocket : public WeaponRocket_t
{
	DGN_WEAPON(Rocket)

public:
	WeaponRocket(Player* player)
	    : WeaponRocket_t(player)
	{
	}
};

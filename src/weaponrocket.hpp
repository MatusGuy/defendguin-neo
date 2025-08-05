// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include "weaponbullet.hpp"
#include "bulletrocket.hpp"
#include "bulletrocket2.hpp"

DGN_WEAPON_BULLET(Rocket, BulletRocket, 2, std::chrono::milliseconds, 500);
class WeaponRocket : public WeaponRocket_t
{
	DGN_WEAPON(Rocket)

public:
	WeaponRocket(Player* player)
	    : WeaponRocket_t(player)
	{
	}
};

DGN_WEAPON_BULLET(Rocket2, BulletRocket2, 2, std::chrono::milliseconds, 400);
class WeaponRocket2 : public WeaponRocket2_t
{
	DGN_WEAPON(Rocket)

public:
	WeaponRocket2(Player* player)
	    : WeaponRocket2_t(player)
	{
	}
};

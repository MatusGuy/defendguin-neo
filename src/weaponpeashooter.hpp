// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include "weaponbullet.hpp"

DGN_WEAPON_BULLET(Peashooter, Bullet, 5, std::chrono::milliseconds, 75);
class WeaponPeashooter : public WeaponPeashooter_t
{
	DGN_WEAPON(Peashooter)

private:
	cog2d::Asset<cog2d::SoundEffect> m_fire_sfx;

public:
	WeaponPeashooter(Player* player);

	void on_fire() override;
};

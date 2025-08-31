// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#include "weaponpeashooter.hpp"

WeaponPeashooter::WeaponPeashooter(Player* player)
    : WeaponPeashooter_t(player)
{
	COG2D_USE_ASSETMANAGER;
	m_fire_sfx = assetmanager.sounds.load_file("sounds/fire.wav");
}

void WeaponPeashooter::on_fire()
{
	m_fire_sfx->play();
}

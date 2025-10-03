// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#include "weaponpeashooter.hpp"

WeaponPeashooter::WeaponPeashooter(Player* player)
    : WeaponPeashooter_t(player)
{
	m_fire_sfx = cog2d::assets::sounds.load_file("sounds/fire.wav");
}

void WeaponPeashooter::on_fire()
{
	cog2d::audio::play_sound(*m_fire_sfx.get());
}

// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include "weapon.hpp"

class WeaponRocket : public Weapon
{
	DGN_WEAPON(Rocket)

public:
	WeaponRocket();

	void init() override;
	void fire() override;
	void update() override;
};


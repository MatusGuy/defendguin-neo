// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only

#include "gameactorfactory.hpp"

#include <cog2d/scene/actormanager.hpp>

#include "enemy.hpp"
#include "enemyfighter.hpp"

GameActorFactory::GameActorFactory()
{
}

cog2d::Actor* GameActorFactory::create(std::string_view cl)
{
	// FIXME: This is terrible. Do an unordered map.

	if (cl == "Enemy") {
		Enemy* e = m_actormanager->create<Enemy>();
		//e->vel() = {0, 0};
		//e->bbox().pos = {300, 100};

		return e;
	}

	if (cl == "EnemyFighter") {
		EnemyFighter* e = m_actormanager->create<EnemyFighter>();
		//e->vel() = {0, 0};
		//e->bbox().pos = {300, 100};

		return e;
	}

	return nullptr;
}

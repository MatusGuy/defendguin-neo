// Copyright (C) 2025 MatusGuy
// SPDX-License-Identifier: LGPL-3.0-only
#pragma once

#include <cog2d/scene/actorfactory.hpp>

class GameActorFactory : public cog2d::ActorFactory
{
public:
	GameActorFactory();

	cog2d::Actor* create(std::string_view cl) override;
};

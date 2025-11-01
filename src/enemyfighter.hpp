#pragma once

#include <cog2d/scene/actor.hpp>
#include <cog2d/util/timer.hpp>
#include <cog2d/assets/assetmanager.hpp>

class EnemyFighter : public cog2d::Actor
{
	COG2D_ACTOR(EnemyFighter)

public:
	EnemyFighter();

public:
	void init() override;
	void update() override;
	void draw() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

protected:
	void add_components() override;

private:
	cog2d::Timer m_timer;
	cog2d::Vector m_origin;
	cog2d::Asset<cog2d::Texture> m_texture;
};

#include "enemyfighter.hpp"

#include <cog2d/video/graphicsengine.hpp>

using namespace std::chrono_literals;

EnemyFighter::EnemyFighter()
{
}

void EnemyFighter::add_components()
{
	add_component<cog2d::ActorComps::Geometry>();
	add_component<cog2d::ActorComps::Velocity>();
	add_component<cog2d::ActorComps::Collision>();
}

void EnemyFighter::init()
{
	bbox() = {{0, 0}, {22, 10}};
	vel() = {0, 0};
}

void EnemyFighter::update()
{
	if (!m_timer.started())
		m_timer.start(1s);

	vel().x = -1.5f;
	vel().y = std::sin(m_timer.get_progress() * 2 * M_PI) * 3.5f;

	cog2d::Actor::update();
}

void EnemyFighter::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect({viewport_pos(), bbox().size}, false, 0xFFC0CBFF);
}

cog2d::CollisionSystem::Response EnemyFighter::collision(cog2d::Actor* other)
{
	return cog2d::CollisionSystem::COLRESP_REJECT;
}

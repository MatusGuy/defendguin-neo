#include "enemybullet.hpp"

#include "enemy.hpp"

#include <cog2d/video/graphicsengine.hpp>

EnemyBullet::EnemyBullet(Enemy* parent)
    : cog2d::Actor(false),
      m_parent(parent)
{
}

void EnemyBullet::init()
{
	col().group = COLGROUP_ENEMYBULLETS;
	bbox() = {{0, 0}, {6, 6}};
}

void EnemyBullet::add_components()
{
	add_component<cog2d::ActorComps::Geometry>();
	add_component<cog2d::ActorComps::Velocity>();
	add_component<cog2d::ActorComps::Collision>();
}

void EnemyBullet::activate(cog2d::Vector pos, cog2d::Vector dir)
{
	bbox().pos = pos;
	vel() = dir;
	vel() *= 5.f;
	set_active(true);
}

void EnemyBullet::deactivate()
{
	vel() = {0.f, 0.f};
	set_active(false);
	m_parent->notify_bullet_deactivate();
}

void EnemyBullet::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect({viewport_pos(), bbox().size}, false, 0xFFA500FF);
}

cog2d::CollisionSystem::Response EnemyBullet::collision(cog2d::Actor* other)
{
	deactivate();
	return cog2d::CollisionSystem::COLRESP_REJECT;
}

#include "enemy.hpp"

#include <cog2d/video/graphicsengine.hpp>
#include <cog2d/scene/actormanager.hpp>
#include <cog2d/scene/actorstage.hpp>

#include "gamescene.hpp"

Enemy::Enemy()
    : cog2d::Actor(),
      m_health(10)
{
}

void Enemy::add_components()
{
	add_component<cog2d::ActorComps::Geometry>();
	add_component<cog2d::ActorComps::Velocity>();
	add_component<cog2d::ActorComps::Collision>();
}

void Enemy::init()
{
	col().group = COLGROUP_ENEMIES;
	bbox() = {0, 0, 15, 15};

	COG2D_USE_ACTORMANAGER;

	for (int i = 0; i < 2; ++i) {
		auto bullet = actormanager.create<EnemyBullet>(this);
		m_bullets.push_front(bullet);
	}
}

void Enemy::draw()
{
	COG2D_USE_GRAPHICSENGINE;
	graphicsengine.draw_rect({viewport_pos(), bbox().size}, false, 0xFF00FFFF);
}

void Enemy::fire()
{
	COG2D_USE_PROGRAM;

	auto& stage = program.get_screen_as<cog2d::ActorStage>();
	auto* gamescene = static_cast<GameScene*>(stage.get_current_scene());
	auto* player = gamescene->get_nearest_player(bbox().pos);

	EnemyBullet* bullet = m_bullets.front();
	// FIXME: this crashes because bbox() doesnt exist. Idk why.
	//bullet->activate(bbox().pos, (player->bbox().pos - bbox().pos).normalized());
}

void Enemy::update()
{
	if (m_timer.check()) {
		fire();
	}

	if (!m_timer.started() && !m_bullets.front()->is_active()) {
		notify_bullet_deactivate();
	}

	if (m_health <= 0)
		set_active(false);
}

cog2d::CollisionSystem::Response Enemy::collision(cog2d::Actor* other)
{
	if (other->col().group == COLGROUP_BULLETS) {
		m_health--;
		return cog2d::CollisionSystem::COLRESP_REJECT;
	}

	return cog2d::Actor::collision(other);
}

cog2d::PropertyRefs Enemy::properties()
{
	cog2d::PropertyRefs out = cog2d::Actor::properties();

	out.push_back(&m_health);

	return out;
}

void Enemy::notify_bullet_deactivate()
{
	m_timer.start(3500ms);
}

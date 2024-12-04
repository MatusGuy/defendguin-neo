#include "player.hpp"

#include <graphicsengine.hpp>
#include <actormanager.hpp>
#include <logger.hpp>

constexpr float SPEED = 5;

Player::Player(int id):
	Actor(),
	m_controller(nullptr),
	m_cooldown(0),
	m_current_bullet(0),
	m_bullets()
{
	m_bbox = {{0,0}, {20, 15}};

	COG2D_USE_INPUTMANAGER;
	m_controller = inputmanager.get_controller(id);
}

void Player::init()
{
	std::pair<Bullet::Type, std::list<Bullet*>> pair;
	auto& bullets = pair.second;
	pair.first = 0;
	bullets.resize(5);

	std::list<Bullet*>::iterator iter;
	for (iter = bullets.begin(); iter != bullets.end(); iter++) {
		Bullet* bullet = new Bullet(this);
		*iter = bullet;
		ActorManager::get().add(bullet);
	}
	m_bullets.insert(pair);
}

void Player::update()
{
	m_vel = {0,0};

	if (m_controller->held(InputActions::DOWN))
	{
		m_vel.y = SPEED;
	}

	if (m_controller->held(InputActions::UP))
	{
		m_vel.y = -SPEED;
	}

	if (m_controller->held(InputActions::RIGHT))
	{
		m_vel.x = SPEED;
	}

	if (m_controller->held(InputActions::LEFT))
	{
		m_vel.x = -SPEED;
	}

	// TODO: proper bullet types
	std::list<Bullet*>& bullets = m_bullets[0];
	Bullet* bullet = bullets.front();
	if (m_controller->held(InputActions::FIRE) && m_cooldown <= 0 && !bullet->is_active())
	{
		m_cooldown = 5;

		bullet->activate({m_bbox.pos.x + m_bbox.size.x, m_bbox.pos.y});
		bullets.splice(bullets.end(), bullets, bullets.begin());
	}

	m_cooldown--;

	Actor::update();
}

void Player::draw()
{
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_rect(m_bbox, true);
}

void Player::notify_bullet_deactivate(Bullet* bullet)
{
	std::list<Bullet*>& bullets = m_bullets[0];
	auto i = std::find(bullets.begin(), bullets.end(), bullet);
	if (i == bullets.end())
		return;

	bullets.splice(bullets.begin(), bullets, i);
}

void Player::next_bullet()
{
	if (m_current_bullet + 1 >= m_bullets[0].size())
		m_current_bullet = 0;
	else
		m_current_bullet++;
}

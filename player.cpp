#include "player.hpp"

#include <graphicsengine.hpp>
#include <actormanager.hpp>

constexpr float SPEED = 5;

Player::Player(int id):
	Actor(),
	m_controller(nullptr)
{
	COG2D_USE_INPUTMANAGER;

	m_bbox = {{0,0}, {50, 25}};

	m_controller = inputmanager.get_controller(id);
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
		m_dir = Dir::RIGHT;
	}

	if (m_controller->held(InputActions::LEFT))
	{
		m_vel.x = -SPEED;
		m_dir = Dir::LEFT;
	}

	if (m_controller->held(InputActions::FIRE) && m_cooldown <= 0)
	{
		m_cooldown = 20;
		auto bullet = ActorManager::get().create<Bullet>(m_dir);

		// TODO: setters
		bullet->get_bbox().pos.y = m_bbox.pos.y;
		if (m_dir == Dir::RIGHT)
			bullet->get_bbox().pos.x = m_bbox.pos.x + m_bbox.size.x;
		else
			bullet->get_bbox().pos.x = m_bbox.pos.x - bullet->get_bbox().size.x;
	}

	m_cooldown--;

	Actor::update();
}

void Player::draw()
{
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_rect(m_bbox, true);
}

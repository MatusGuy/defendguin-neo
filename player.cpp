#include "player.hpp"

#include "graphicsengine.hpp"
#include "constants.hpp"

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
	}

	if (m_controller->held(InputActions::LEFT))
	{
		m_vel.x = -SPEED;
	}

	Actor::update();
}

void Player::draw()
{
	COG2D_USE_GRAPHICSENGINE;

	graphicsengine.draw_rect(m_bbox, true);
}

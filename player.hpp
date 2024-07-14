#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <actor.hpp>
#include <inputmanager.hpp>

#include "bullet.hpp"

class Player : public Actor
{
private:
	Controller* m_controller;
	Dir m_dir;
	int m_cooldown;

public:
	Player(int id = 0);

	void update() override;
	void draw() override;

};

#endif // PLAYER_HPP

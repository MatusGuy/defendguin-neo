#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <actor.hpp>
#include <inputmanager.hpp>

class Player : public Actor
{
private:
	Controller* m_controller;

public:
	Player(int id = 0);

	void update() override;
	void draw() override;

};

#endif // PLAYER_HPP

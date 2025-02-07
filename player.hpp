#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>

#include <actor.hpp>
#include <inputmanager.hpp>

#include "bullet.hpp"

class Player : public Actor
{
private:
	Controller* m_controller;
	int m_cooldown;

	int m_current_bullet;
	std::unordered_map<Bullet::Type, std::list<Bullet*>> m_bullets;

	Texture* m_texture;

public:
	Player(int id = 0);


	void init();
	void update() override;
	void draw() override;


private:
	friend class Bullet;

	void notify_bullet_deactivate(Bullet* bullet);

	void next_bullet();
};

#endif // PLAYER_HPP

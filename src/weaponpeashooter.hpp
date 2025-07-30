#pragma once

#include <forward_list>

#include <cog2d/util/timer.hpp>

#include "bullet.hpp"
#include "weapon.hpp"

class WeaponPeashooter : public Weapon
{
	DGN_WEAPON(Peashooter)

public:
	std::forward_list<Bullet*> m_bullets;
	std::forward_list<Bullet*>::iterator m_current_bullet;

	cog2d::Timer m_cooldown;

public:
	WeaponPeashooter(Player* player);

	void init() override;
	void fire() override;
	//void notify_bullet_deactivate(void* bullet_) override;
	void update() override;
	//void draw() override;
};

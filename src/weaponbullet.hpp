#pragma once

#include <forward_list>

#include <cog2d/util/timer.hpp>
#include <cog2d/util/typetraits.hpp>
#include <cog2d/scene/actormanager.hpp>

#include "constants.hpp"
#include "bullet.hpp"
#include "weapon.hpp"
#include "player.hpp"

#define DGN_WEAPON_BULLET(name, bullet, ...) \
	using Weapon##name##_t = WeaponBullet<bullet, __VA_ARGS__>

struct WeaponBulletParams
{
	std::uint8_t max_bullets;
	cog2d::Duration cooldown;
};

template<class T, std::uint8_t max_bullets, typename Duration_t = std::chrono::milliseconds,
         Duration_t::rep cooldown = 0>
class WeaponBullet : public Weapon
{
public:
	std::forward_list<T*> m_bullets;
	std::forward_list<T*>::iterator m_current_bullet;

	cog2d::Timer m_cooldown;

public:
	WeaponBullet(Player* player)
	    : Weapon(player),
	      m_bullets(),
	      m_current_bullet(m_bullets.begin()),
	      m_cooldown()
	{
	}

	virtual Type type() = 0;
	void init() override
	{
		COG2D_USE_ACTORMANAGER;

		m_bullets.resize(max_bullets);
		typename std::forward_list<T*>::iterator iter;
		for (iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
			*iter = actormanager.create<T>(this);
		}
		m_current_bullet = m_bullets.begin();
	}

	void fire() override
	{
		if (m_cooldown.started())
			return;

		T* bullet = *m_current_bullet;

		if (bullet->is_active())
			return;

		bullet->activate({m_player->bbox().get_right(),
		                  m_player->bbox().get_top() + (m_player->bbox().size.y / 2)});

		++m_current_bullet;
		if (m_current_bullet == m_bullets.end())
			m_current_bullet = m_bullets.begin();

		m_cooldown.start(Duration_t(cooldown));
	}

	//void notify_bullet_deactivate(void* bullet_) override;
	void update() override { m_cooldown.check(); }
	//void draw() override;
};

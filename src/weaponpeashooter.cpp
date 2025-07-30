#include "weaponpeashooter.hpp"

#include <cog2d/scene/actormanager.hpp>

#include "player.hpp"

constexpr int MAX_BULLETS = 2;
constexpr int COOLDOWN = 75;

WeaponPeashooter::WeaponPeashooter(Player* player)
    : Weapon(player),
      m_bullets(),
      m_current_bullet(m_bullets.begin()),
      m_cooldown()
{
}

void WeaponPeashooter::init()
{
	COG2D_USE_ACTORMANAGER;

	m_bullets.resize(MAX_BULLETS);
	std::forward_list<Bullet*>::iterator iter;
	for (iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
		*iter = actormanager.create<Bullet>(this);
	}
	m_current_bullet = m_bullets.begin();
}

void WeaponPeashooter::fire()
{
	if (m_cooldown.started())
		return;

	Bullet* bullet = *m_current_bullet;

	if (bullet->is_active())
		return;

	bullet->activate({m_player->bbox().get_right(),
	                  m_player->bbox().get_top() + (m_player->bbox().size.y / 2)});

	++m_current_bullet;
	if (m_current_bullet == m_bullets.end())
		m_current_bullet = m_bullets.begin();

	m_cooldown.start(COOLDOWN);
}

void WeaponPeashooter::update()
{
	m_cooldown.check();
}

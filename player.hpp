#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>

#include <cog2d/scene/actor.hpp>
#include <cog2d/input/inputmanager.hpp>

#include "bullet.hpp"

class Player : public cog2d::Actor
{
private:
	cog2d::Controller* m_controller;
	int m_cooldown;

	int m_current_bullet;
	std::unordered_map<Bullet::Type, std::list<Bullet*>> m_bullets;

	cog2d::AssetKey<cog2d::Texture> m_texture;

public:
	Player(int id = 0);

	void init(cog2d::ActorManager& actormanager);
	void update() override;
	void draw() override;


private:
	friend class Bullet;

	void notify_bullet_deactivate(Bullet* bullet);

	void next_bullet();
};

#endif // PLAYER_HPP

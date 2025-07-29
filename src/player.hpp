#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>

#include "constants.hpp"
#include <cog2d/scene/actor.hpp>
#include <cog2d/input/inputmanager.hpp>

#include "bullet.hpp"

class Player : public cog2d::Actor
{
	COG2D_ACTOR(Player)

	friend class Bullet;

public:
	cog2d::Controller* m_controller;
	int m_cooldown;

	int m_current_bullet;
	std::unordered_map<Bullet::Type, std::list<Bullet*>> m_bullets;

	cog2d::Asset<cog2d::Texture> m_texture;

public:
	Player();

	void init() override;
	void update() override;
	void draw() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

protected:
	void add_components() override;

private:
	void notify_bullet_deactivate(Bullet* bullet);

	void next_bullet();
};

#endif  // PLAYER_HPP

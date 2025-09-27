#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <forward_list>

#include "constants.hpp"
#include <cog2d/scene/actor.hpp>
#include <cog2d/input/inputmanager.hpp>
#include <cog2d/assets/assetmanager.hpp>

#include "weapon.hpp"

class Player : public cog2d::Actor
{
	COG2D_ACTOR(Player)

	friend class Bullet;

public:
	cog2d::ControllerId m_controller;

	std::unordered_map<Weapon::Type, std::unique_ptr<Weapon>> m_weapons;
	Weapon* m_current_weapon;

	cog2d::Asset<cog2d::Texture> m_texture;

public:
	Player();

	void init() override;
	void update() override;
	void draw() override;
	cog2d::CollisionSystem::Response collision(cog2d::Actor* other) override;

protected:
	void add_components() override;
};

#endif  // PLAYER_HPP

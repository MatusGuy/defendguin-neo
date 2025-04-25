#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <scene.hpp>
#include <bitmapfont.hpp>
#include <tilemap.hpp>

#include "player.hpp"

class GameScene : public cog2d::Scene
{
public:
	GameScene();
	~GameScene();

	void init() override;
	void draw() override;

	cog2d::BitmapFont* m_font = nullptr;
	cog2d::Texture* m_text = nullptr;
	Player* m_player = nullptr;
	cog2d::TileMap* m_map = nullptr;
};

#endif // GAMESCENE_H

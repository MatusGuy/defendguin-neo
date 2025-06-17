#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <cog2d/scene/actorstage.hpp>
#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/scene/tilemap/tilemap.hpp>

#include "player.hpp"

class GameScene : public cog2d::ActorStage
{
public:
	GameScene();
	~GameScene();

	void init() override;
	void draw() override;

	cog2d::PixmapFont* m_font = nullptr;
	std::unique_ptr<cog2d::Texture> m_text = nullptr;
	Player* m_player = nullptr;
	cog2d::TileMap* m_map = nullptr;
};

#endif // GAMESCENE_H

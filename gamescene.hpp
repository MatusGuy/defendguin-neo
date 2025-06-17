#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <cog2d/scene/tilemap/tilescene.hpp>
#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/scene/tilemap/tilemap.hpp>

#include "camera.hpp"
#include "player.hpp"

class GameScene : public cog2d::TileScene
{
public:
	GameScene();
	~GameScene();

	void init() override;
	void draw() override;

	cog2d::PixmapFont* m_font = nullptr;
	std::unique_ptr<cog2d::Texture> m_text = nullptr;
	Player* m_player = nullptr;
	Camera m_camera;
};

#endif // GAMESCENE_H

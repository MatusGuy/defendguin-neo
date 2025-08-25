#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "constants.hpp"
#include <cog2d/scene/tilemap/tilescene.hpp>
#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/scene/tilemap/tilemap.hpp>
#include <cog2d/audio/musictrack.hpp>

#include "camera.hpp"
#include "player.hpp"
#include "gameactorfactory.hpp"

class GameScene : public cog2d::TileScene
{
public:
	GameScene();
	~GameScene();

	void init() override;
	void draw() override;

	Player* get_nearest_player(const cog2d::Vector& pos);

	cog2d::Asset<cog2d::PixmapFont> m_font;
	std::unique_ptr<cog2d::Texture> m_text = nullptr;
	Player* m_player = nullptr;
	Camera m_camera;
	GameActorFactory m_factory;
	cog2d::Asset<cog2d::MusicTrack> m_music;
};

#endif  // GAMESCENE_H

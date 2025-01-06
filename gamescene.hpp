#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <scene.hpp>
#include <bitmapfont.hpp>

#include "player.hpp"

class GameScene : public Scene
{
public:
	GameScene();

	void init() override;
	void draw() override;

	BitmapFont* m_font = nullptr;
	Texture* m_text = nullptr;
	Player* m_player = nullptr;
};

#endif // GAMESCENE_H

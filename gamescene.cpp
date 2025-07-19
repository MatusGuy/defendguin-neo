#include "gamescene.hpp"

#include <cog2d/scene/viewport.hpp>
#include <cog2d/scene/actorstage.hpp>
#include <cog2d/scene/tilemap/bintilemapparser.hpp>

#include "constants.hpp"
#include "enemy.hpp"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	COG2D_USE_INPUTMANAGER;
	COG2D_USE_VIEWPORT;

	cog2d::TileScene::init();

	if (std::filesystem::exists(std::filesystem::path(COG2D_ASSET_PATH) / "font.png")) {
		m_font = new cog2d::PixmapFont();
		m_font->set_horizontal_spacing(1);
		m_font->load(cog2d::AssetFile("font.png"));

		m_text = m_font->create_text("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	}

	// TODO: function to register collision groups
	m_actormanager.colsystem().m_groups.push_back({0, 0, 1});  // PLAYERS
	m_actormanager.colsystem().m_groups.push_back({0, 0, 1});  // BULLETS
	m_actormanager.colsystem().m_groups.push_back({1, 1, 0});  // ENEMIES

	m_player = m_actormanager.create<Player>();
	m_player->col().heavy = false;
	m_player->bbox().pos.y = 50;
	m_player->m_controller = inputmanager.get_controller(0);

	//auto plr2 = m_actormanager.create<Player>(1);
	//plr2->m_group = 0;
	//plr2->m_static = false;
	//plr2->init(m_actormanager);

	Enemy* e = m_actormanager.create<Enemy>();
	e->vel() = {0, 0};
	e->bbox().pos = {250, 100};

	// TODO: Make generic Map or MapParser class to handle both actors and tilemaps
	cog2d::AssetFile file("cool.dat");
	file.open(cog2d::IoDevice::OPENMODE_READ | cog2d::IoDevice::OPENMODE_BINARY);
	cog2d::BinTileMapParser parser;
	parser.parse(file, m_map);

	viewport.set_camera(&m_camera);
}

void GameScene::draw()
{
	cog2d::TileScene::draw();

	//COG2D_USE_GRAPHICSENGINE;
	//if (m_text)
	//	graphicsengine.draw_texture({{0, 1}, {-1, -1}}, m_text.get());
}

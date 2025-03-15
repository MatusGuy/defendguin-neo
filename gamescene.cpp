#include "gamescene.hpp"

#include "constants.hpp"
#include "enemy.hpp"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	delete m_map;
}

void GameScene::init()
{
	Scene::init();

	if (std::filesystem::exists(std::filesystem::path(COG2D_ASSET_PATH) / "font.png")) {
		m_font = new BitmapFont("font.png");
		m_font->set_horizontal_spacing(1);
		m_font->load();

		m_text = m_font->create_text("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	}

	// TODO: function to register collision groups
	m_collisionsystem.m_groups.push_back({0, 0, 1}); // PLAYERS
	m_collisionsystem.m_groups.push_back({0, 0, 1}); // BULLETS
	m_collisionsystem.m_groups.push_back({1, 1, 0}); // ENEMIES

	m_player = m_actormanager.create<Player>(0);
	m_player->m_group = 0;
	m_player->m_static = false;
	m_player->init(m_actormanager);

	//auto plr2 = m_actormanager.create<Player>(1);
	//plr2->m_group = 0;
	//plr2->m_static = false;
	//plr2->init(m_actormanager);

	Enemy* e = m_actormanager.create<Enemy>();
	e->m_vel = {0, 0};
	e->m_bbox.pos = {150, 100};

	m_map = new TileMap;
	m_map->parse("testlvl.json");
}

void GameScene::draw()
{
	Scene::draw();

	m_map->draw();
	COG2D_USE_GRAPHICSENGINE;
	if (m_text)
		graphicsengine.draw_texture({{0,1}, {-1,-1}}, m_text);
}

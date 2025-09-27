#include "gamescene.hpp"

#include <cog2d/scene/viewport.hpp>
#include <cog2d/scene/actorstage.hpp>
#include <cog2d/scene/tilemap/bintilemapparser.hpp>
#include <cog2d/audio/musicplayer.hpp>

#include "enemy.hpp"
#include "enemyfighter.hpp"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	m_actormanager.allow_active_type_indexing<Player>();

	COG2D_USE_ASSETMANAGER;
	COG2D_USE_VIEWPORT;
	COG2D_USE_MUSICPLAYER;

	cog2d::TileScene::init();

	m_actormanager.set_factory(&m_factory);

	if (std::filesystem::exists(std::filesystem::path(COG2D_ASSET_PATH) / "fonts/font.toml")) {
		m_font = assetmanager.pixmapfonts.load_file("fonts/font.toml");

		m_text = m_font->create_text("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	}

	// TODO: function to register collision groups
	// clang-format off
	m_actormanager.colsystem().m_groups.assign({
	//   PLAYERS, BULLETS, ENEMIES, ENEMYBULLETS
	    {0,       0,       1,       1           }, // PLAYERS
	    {0,       0,       1,       0           }, // BULLETS
	    {1,       1,       0,       0           }, // ENEMIES
	    {1,       0,       0,       0           }  // ENEMYBULLETS
	});
	// clang-format on

	m_player = m_actormanager.create<Player>();
	m_player->col().heavy = false;
	m_player->bbox().pos.y = 50;
	m_player->m_controller = cog2d::input::get_controller(0);

	//auto plr2 = m_actormanager.create<Player>(1);
	//plr2->m_group = 0;
	//plr2->m_static = false;
	//plr2->init(m_actormanager);

	cog2d::AssetFile file("levels/cool.dat");
	file.open(cog2d::IoDevice::OPENMODE_READ | cog2d::IoDevice::OPENMODE_BINARY);
	cog2d::new_parse<cog2d::BinTileMapParser>(file, m_map, m_actormanager);
	file.close();

	m_music = assetmanager.musictracks.load_file("music/music.toml");
	musicplayer.set_track(m_music.get());

	viewport.set_camera(&m_camera);
}

void GameScene::draw()
{
	cog2d::TileScene::draw();

	//COG2D_USE_GRAPHICSENGINE;
	//if (m_text)
	//	cog2d::graphics::draw_texture({{0, 1}, {-1, -1}}, m_text.get());
}

Player* GameScene::get_nearest_player(const cog2d::Vector& pos)
{
	auto players = m_actormanager.get_active_actors_of_type<Player>();
	Player* out = nullptr;
	float dist = 0;
	for (auto it = players.begin(); it != players.end(); ++it) {
		auto player = static_cast<Player*>(*it);
		if (out == nullptr || dist > pos.distance(player->bbox().pos))
			out = player;
	}
	return out;
}

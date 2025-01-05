#include <iostream>

#define COG2D_GRAPHICS_USE_INT

#include <bitmapfont.hpp>
#include <program.hpp>

#include "constants.hpp"
#include "player.hpp"

class Game : public Program {
public:
	BitmapFont* m_font = nullptr;
	Texture* m_text = nullptr;
	Player* m_player = nullptr;

public:
	Game(): Program() {
		m_settings->title = "Defendguin NEO";

		m_settings->set_size((224 * 16) / 9, 224);
		m_settings->wwidth *= 2;
		m_settings->wheight *= 2;

		// #retro
		m_settings->scale_quality = "nearest";

		m_settings->systems ^= System::SYSTEM_CONFIG;
	}

	void init() override {
		// FIXME: Hahahahahaha FIX THE PATHS!!!!

		if (std::filesystem::exists("D:/Programming/CPP/defendguin2/font.png")) {
			m_font = new BitmapFont("D:/Programming/CPP/defendguin2/font.png");
			m_font->set_horizontal_spacing(1);
			m_font->load();

			m_text = m_font->create_text("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
		}

		COG2D_USE_COLLISIONSYSTEM;
		collisionsystem.m_groups.push_back({1, 1});
		collisionsystem.m_groups.push_back({1, 1});

		m_player = ActorManager::get().create<Player>(0);
		m_player->m_group = 0;
		m_player->m_static = true;
		m_player->init();

		Bullet* b = new Bullet(m_player);
		b->m_bbox.pos = {300, 100};
		b->m_vel = {-.5, 0};
		b->m_group = 1;
		b->m_active = true;
		ActorManager::get().add(b);


	}

	void update() override {}
	void draw() override {
		COG2D_USE_GRAPHICSENGINE;
		if (m_text)
			graphicsengine.draw_texture({{0,1}, {-1,-1}}, m_text);
	}

	bool event(SDL_Event* ev) override {

		if (ev->type == SDL_KEYDOWN && ev->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			m_keep_running = false;
			return false;
		}

		return true;
	}

	bool register_actions() override {
		InputAction action = {
			InputActions::DOWN, // action id
			"down", // name
			"Down", // display name

			{
				// controller type, input id
				{ 1, SDL_SCANCODE_S },
				{ 2, 0 },
			}
		};
		InputManager::get().register_action(action);

		action = {
			InputActions::UP, // action id
			"up", // name
			"Up", // display name

			{
				// controller type, input id
				{ 1, SDL_SCANCODE_W },
				{ 2, 0 },
			}
		};
		InputManager::get().register_action(action);

		action = {
			InputActions::RIGHT, // action id
			"right", // name
			"Right", // display name

			{
				// controller type, input id
				{ 1, SDL_SCANCODE_D },
				{ 2, 0 },
			}
		};
		InputManager::get().register_action(action);

		action = {
			InputActions::LEFT, // action id
			"left", // name
			"Left", // display name

			{
				// controller type, input id
				{ 1, SDL_SCANCODE_A },
				{ 2, 0 },
			}
		};
		InputManager::get().register_action(action);

		action = {
			InputActions::FIRE, // action id
			"fire", // name
			"Fire", // display name

			{
				// controller type, input id
				{ 1, SDL_SCANCODE_RSHIFT },
				{ 2, 0 },
			}
		};
		InputManager::get().register_action(action);

		return true;
	}
};

int main(int argc, char* argv[]) {
	Game game;
	return game.run(argc, argv);
}

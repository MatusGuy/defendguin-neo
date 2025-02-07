#include <iostream>

#define COG2D_GRAPHICS_USE_INT

#include <bitmapfont.hpp>
#include <program.hpp>

#include "gamescene.hpp"
#include "cog2dintro.hpp"

class Game : public Program {
public:
	Game(): Program() {
		m_settings->title = "Defendguin NEO";

		m_settings->set_size((240 * 4) / 3, 240);
		m_settings->wwidth *= 2;
		m_settings->wheight *= 2;

		// #retro
		m_settings->scale_quality = "nearest";
		m_settings->proxy_texture = true;

		m_settings->systems ^= System::SYSTEM_CONFIG;
	}

	void init() override {
		push_screen(new GameScene);
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

COG2D_MAIN(Game)

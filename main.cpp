#include <iostream>
#include <program.hpp>

#include "constants.hpp"
#include "player.hpp"

class Game : public Program {
public:
	Player* m_player;

public:
	Game(): Program() {
		m_settings->systems ^= System::SYSTEM_CONFIG;
	}

	void init() override {
		m_player = ActorManager::get().create<Player>(0);
	}

	void update() override {}
	void draw() override {}

	bool event(SDL_Event* ev) override { return true; }

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

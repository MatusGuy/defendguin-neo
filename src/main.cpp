#include <iostream>

#include "constants.hpp"

#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/program.hpp>
#include <cog2d/scene/actorstage.hpp>

#include "gamescene.hpp"
#include "cog2dintro.hpp"

#include <execinfo.h>

class Game : public cog2d::Program
{
public:
	GameScene m_scene;

public:
	Game()
	    : cog2d::Program()
	{
		m_settings->title = "Defendguin NEO";

		m_settings->set_size((240 * 4) / 3, 240);
		m_settings->wwidth *= 2;
		m_settings->wheight *= 2;

		// #retro
		m_settings->scale_quality = "nearest";
		m_settings->proxy_texture = true;

		m_settings->vsync = false;

		m_settings->systems ^= cog2d::System::SYSTEM_CONFIG;
	}

	void init() override
	{
#if 1
		// Test game scene

		auto stage = std::make_unique<cog2d::ActorStage>();
		stage->set_current_scene(&m_scene);
		push_screen(std::move(stage));
#else
		// Test cog2d intro
		push_screen(std::make_unique<Cog2dIntro>());
#endif
	}

	bool event(SDL_Event* ev) override
	{
		if (ev->type == SDL_KEYDOWN && ev->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			m_keep_running = false;
			return false;
		}

		return true;
	}

	bool register_actions() override
	{
		cog2d::input::register_action({
		    InputActions::UP,              // action id
		    "Up",                          // display name
		    SDL_SCANCODE_W,                // default keyboard scancode
		    0,                             // default generic joystick button
		    SDL_CONTROLLER_BUTTON_DPAD_UP  // default game controller button
		});

		cog2d::input::register_action({
		    InputActions::DOWN,              // action id
		    "Down",                          // display name
		    SDL_SCANCODE_S,                  // default keyboard scancode
		    0,                               // default generic joystick button
		    SDL_CONTROLLER_BUTTON_DPAD_DOWN  // default game controller button
		});

		cog2d::input::register_action({
		    InputActions::LEFT,              // action id
		    "Left",                          // display name
		    SDL_SCANCODE_A,                  // default keyboard scancode
		    0,                               // default generic joystick button
		    SDL_CONTROLLER_BUTTON_DPAD_LEFT  // default game controller button
		});

		cog2d::input::register_action({
		    InputActions::RIGHT,              // action id
		    "Right",                          // display name
		    SDL_SCANCODE_D,                   // default keyboard scancode
		    0,                                // default generic joystick button
		    SDL_CONTROLLER_BUTTON_DPAD_RIGHT  // default game controller button
		});

		cog2d::input::register_action({
		    InputActions::FIRE,      // action id
		    "Fire",                  // display name
		    SDL_SCANCODE_RSHIFT,     // default keyboard scancode
		    0,                       // default generic joystick button
		    SDL_CONTROLLER_BUTTON_A  // default game controller button
		});

		return true;
	}
};

COG2D_MAIN(Game)

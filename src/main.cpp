#include <iostream>

#include "constants.hpp"

#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/program.hpp>
#include <cog2d/video/graphicsengine.hpp>

#include "entity.hpp"

static Entity s_ecs[100] = {0};
static int s_entity_count = 0;

void init()
{
	Entity& ent = s_ecs[0];
	ent.bbox = {{100, 100}, {10, 10}};
	s_entity_count = 1;
}

void draw()
{
	//cog2d::TileScene::draw();

	for (int i = 0; i < s_entity_count; ++i) {
		Entity& ent = s_ecs[i];
		cog2d::graphics::draw_rect(ent.bbox, false, 0xFF0000FF);
	}
	//if (m_text)
}

void update()
{
	/*
	for (int i = 0; i < s_entity_count; ++i) {
		Entity& ent = s_ecs[i];
	}
	*/
}

/*
Player* get_nearest_player(const cog2d::Vector& pos)
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
*/

namespace cog2d::program::ext {

void program_settings(ProgramSettings& settings)
{
	settings.title = "Defendguin NEO";

	settings.set_size((240 * 4) / 3, 240);
	settings.wwidth *= 2;
	settings.wheight *= 2;

	// #retro
	settings.scale_quality = "nearest";
	settings.proxy_texture = true;

	settings.vsync = false;

	settings.systems ^= cog2d::System::SYSTEM_CONFIG;
}

void init()
{
	::init();
}

void draw()
{
	::draw();
}

void update()
{
	::update();
}

bool event(SDL_Event* ev)
{
	if (ev->type == SDL_KEYDOWN && ev->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		s_program.keep_running = false;
		return false;
	}

	return true;
}

void register_actions()
{
	cog2d::input::register_action({
	    InputActions::UP,              // action id
	    "Up",                          // display name
	    SDL_SCANCODE_W,                // default keyboard scancode
	    HAT_UP,                        // default generic joystick button
	    SDL_CONTROLLER_BUTTON_DPAD_UP  // default game controller button
	});

	cog2d::input::register_action({
	    InputActions::DOWN,              // action id
	    "Down",                          // display name
	    SDL_SCANCODE_S,                  // default keyboard scancode
	    HAT_DOWN,                        // default generic joystick button
	    SDL_CONTROLLER_BUTTON_DPAD_DOWN  // default game controller button
	});

	cog2d::input::register_action({
	    InputActions::LEFT,              // action id
	    "Left",                          // display name
	    SDL_SCANCODE_A,                  // default keyboard scancode
	    HAT_LEFT,                        // default generic joystick button
	    SDL_CONTROLLER_BUTTON_DPAD_LEFT  // default game controller button
	});

	cog2d::input::register_action({
	    InputActions::RIGHT,              // action id
	    "Right",                          // display name
	    SDL_SCANCODE_D,                   // default keyboard scancode
	    HAT_RIGHT,                        // default generic joystick button
	    SDL_CONTROLLER_BUTTON_DPAD_RIGHT  // default game controller button
	});

	cog2d::input::register_action({
	    InputActions::FIRE,      // action id
	    "Fire",                  // display name
	    SDL_SCANCODE_RSHIFT,     // default keyboard scancode
	    0,                       // default generic joystick button
	    SDL_CONTROLLER_BUTTON_A  // default game controller button
	});

	cog2d::input::register_joy_axis_converter(0, {InputActions::LEFT, InputActions::RIGHT});
	cog2d::input::register_joy_axis_converter(1, {InputActions::UP, InputActions::DOWN});
}

void load_config(const TomlTable& table)
{
}
void save_config(TomlTable& table)
{
}
void register_config()
{
}

}  //namespace cog2d::program::ext

COG2D_MAIN

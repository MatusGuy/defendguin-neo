#include "cog2dintro.hpp"

#include <cog2d/util/logger.hpp>
#include <cog2d/video/graphicsengine.hpp>

#include "constants.hpp"

namespace intro_cog2d {

enum State : std::uint8_t
{
	STRETCHING,
	INTERVAL,
	FLIPPING_START,
	FLIPPING_END,
	MOVE,
	SHOW_TEXT
};

static struct
{
	cog2d::Texture* title;
	float y_pos = 0;
	cog2d::Vector title_size{0, 0};
	cog2d::Color title_color;

	cog2d::Timer timer;
	State state = STRETCHING;
	State next_state = INTERVAL;
	cog2d::graphics::Flip flip = cog2d::graphics::FLIP_HORIZONTAL;
	cog2d::Color bg_color = 0xFFFFFFFF;

	cog2d::PixmapFont* font;
	std::string text;
	float cover_width;
	bool draw_text = false;

	// FIXME: There should of course be a way to automate the creation of text textures.
	std::unique_ptr<cog2d::Texture> text_texture;
} s_state;

inline bool text_shown()
{
	return s_state.state == State::SHOW_TEXT || s_state.cover_width == 0;
}

void init()
{
	cog2d::assets::load_pixmap(0, "images/cog2d.png", s_state.title);
	s_state.title_size = s_state.title->size();
	s_state.title_size.x = 0;

	s_state.y_pos = static_cast<float>(cog2d::graphics::logical_size().y) / 2.f;

	cog2d::assets::load_pixmapfont(0, "fonts/font.toml", s_state.font);

	SDL_version version;
	SDL_GetVersion(&version);
	s_state.text = cog2d::fmt::format("SDL {} {} {}", version.major, version.minor, version.patch);
	s_state.text_texture.reset(s_state.font->create_text(s_state.text));
	s_state.cover_width = static_cast<float>(s_state.text_texture->size().x);

	// TODO: abstract this
	//SDL_SetTextureBlendMode(s_state.title->get_sdl_texture(), SDL_BLENDMODE_ADD);
	SDL_SetTextureColorMod(static_cast<SDL_Texture*>(s_state.title->data()), 0, 0, 0);
}

void update()
{
	// TODO: state machine class?
	switch (s_state.state) {
	case STRETCHING:
		if (s_state.timer.check()) {
			s_state.state = INTERVAL;
			s_state.next_state = FLIPPING_START;
			s_state.timer.start(500ms);
			break;
		}

		if (!s_state.timer.started()) {
			s_state.timer.start(1s);
			break;
		}

		s_state.title_size.x = s_state.timer.progress() * s_state.title->size().x;

		break;

	case INTERVAL:
		if (s_state.timer.check()) {
			s_state.state = s_state.next_state;
		}
		break;

	case FLIPPING_START: {
		if (s_state.timer.check()) {
			s_state.flip = cog2d::graphics::FLIP_NONE;
			s_state.state = FLIPPING_END;
			break;
		}

		if (!s_state.timer.started()) {
			s_state.timer.start(1s);
			break;
		}

		auto bgcolor = static_cast<std::uint8_t>((1.f - (s_state.timer.progress() / 2)) * 255.f);
		s_state.bg_color.r = bgcolor;
		s_state.bg_color.g = bgcolor;
		s_state.bg_color.b = bgcolor;

		s_state.title_size.y = (1.f - s_state.timer.progress()) * s_state.title->size().y;

		break;
	}

	case FLIPPING_END: {
		if (s_state.timer.check()) {
			s_state.timer.start(500ms);
			s_state.state = INTERVAL;
			s_state.next_state = MOVE;
			break;
		}

		if (!s_state.timer.started()) {
			s_state.timer.start(1s);
			break;
		}

		auto color = static_cast<std::uint8_t>((.5f + (s_state.timer.progress() / 2)) * 255.f);
		SDL_SetTextureColorMod(static_cast<SDL_Texture*>(s_state.title->data()), color, color,
		                       color);

		auto bgcolor = static_cast<std::uint8_t>((1.5f - (s_state.timer.progress() / 2)) * 255.f);
		s_state.bg_color.r = bgcolor;
		s_state.bg_color.g = bgcolor;
		s_state.bg_color.b = bgcolor;

		s_state.title_size.y = s_state.timer.progress() * s_state.title->size().y;

		break;
	}

	case MOVE: {
		if (s_state.timer.check()) {
			// TODO: End
			s_state.timer.start(500ms);
			s_state.state = INTERVAL;
			s_state.next_state = SHOW_TEXT;
			break;
		}

		if (!s_state.timer.started()) {
			s_state.timer.start(1s);
			break;
		}

		;
		auto ycenter = static_cast<float>(cog2d::graphics::logical_size().y) / 2.f;
		s_state.y_pos = (ycenter) - (75.f * s_state.timer.progress());

		break;
	}

	case SHOW_TEXT: {
		if (s_state.timer.check()) {
			// TODO: End
			s_state.cover_width = 0;
			s_state.timer.start(10s);
			s_state.state = INTERVAL;
			s_state.next_state = FLIPPING_START;
			break;
		}

		if (!s_state.timer.started()) {
			s_state.timer.start(1500ms);
			s_state.draw_text = true;
		}

		s_state.cover_width = (1.f - s_state.timer.progress()) * s_state.text_texture->size().x;

		break;
	}

	default:
		break;
	}
}

void draw()
{
	cog2d::Vector size(cog2d::graphics::logical_size());
	//Vector center = {sizef.x / 2.f, sizef.y / 2.f};
	//cog2d::graphics::draw_texture({center, {s_state.title_size.x, 1.f}}, s_state.title, 0.f,
	//s_state.flip);

	cog2d::graphics::draw_rect({{0, 0}, {size.x, size.y}}, true, s_state.bg_color);

	cog2d::Vector center = {size.x / 2.f, size.y / 2.f};
	cog2d::Vector titlepos = {center.x, s_state.y_pos};
	cog2d::graphics::draw_texture(s_state.title,
	                              {titlepos - (s_state.title_size / 2), s_state.title_size},
	                              s_state.bg_color.inverted(), s_state.flip);

	if (s_state.draw_text) {
		cog2d::Vector texsizef = {static_cast<float>(s_state.text_texture->size().x),
		                          static_cast<float>(s_state.text_texture->size().y)};
		cog2d::Vector pos = {center.x - (texsizef.x / 2.f), center.y - (texsizef.y / 2.f) + 20};
		cog2d::graphics::draw_texture(s_state.text_texture.get(), pos);
		//s_state.font->write_text(nullptr, s_state.text, pos);

		cog2d::graphics::draw_rect({{pos.x + (texsizef.x - std::floor(s_state.cover_width)), pos.y},
		                            {s_state.cover_width, texsizef.y}},
		                           true, 0xFF000000);
	}

	//cog2d::graphics::draw_point({0, 0}, 0xFF0000FF);
}

bool event(SDL_Event* ev)
{
	return true;
}

}  //namespace intro_cog2d

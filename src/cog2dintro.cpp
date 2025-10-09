#include "cog2dintro.hpp"

#include <cog2d/util/logger.hpp>
#include <cog2d/video/graphicsengine.hpp>

#include "constants.hpp"

Cog2dIntro::Cog2dIntro()
    : m_title(),
      m_y_pos(0),
      m_title_size(0, 0),
      m_timer(),
      m_state(State::STRETCHING),
      m_next_state(State::INTERVAL),
      m_flip(cog2d::graphics::FLIP_HORIZONTAL),
      m_bg_color(0xFFFFFFFF),
      m_draw_text(false)
{
}

void Cog2dIntro::init()
{
	m_title = cog2d::assets::pixmaps.load_file("images/cog2d.png");
	m_title_size = m_title->size();
	m_title_size.x = 0;

	m_y_pos = static_cast<float>(cog2d::graphics::get_logical_size().y) / 2.f;

	m_font = cog2d::assets::pixmapfonts.load_file("fonts/font.toml");

	SDL_version version;
	SDL_GetVersion(&version);
	m_text = cog2d::fmt::format("SDL {} {} {}", version.major, version.minor, version.patch);
	m_text_texture.reset(m_font->create_text(m_text));
	m_cover_width = static_cast<float>(m_text_texture->size().x);

	// TODO: abstract this
	//SDL_SetTextureBlendMode(m_title->get_sdl_texture(), SDL_BLENDMODE_ADD);
	SDL_SetTextureColorMod(static_cast<SDL_Texture*>(m_title->data()), 0, 0, 0);
}

void Cog2dIntro::update()
{
	// TODO: state machine class?
	switch (m_state) {
	case State::STRETCHING:
		if (m_timer.check()) {
			m_state = State::INTERVAL;
			m_next_state = State::FLIPPING_START;
			m_timer.start(500ms);
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1s);
			break;
		}

		m_title_size.x = m_timer.get_progress() * m_title->m_size.x;

		break;

	case State::INTERVAL:
		if (m_timer.check()) {
			m_state = m_next_state;
		}
		break;

	case State::FLIPPING_START: {
		if (m_timer.check()) {
			m_flip = cog2d::graphics::FLIP_NONE;
			m_state = State::FLIPPING_END;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1s);
			break;
		}

		auto bgcolor = static_cast<std::uint8_t>((1.f - (m_timer.get_progress() / 2)) * 255.f);
		m_bg_color.r = bgcolor;
		m_bg_color.g = bgcolor;
		m_bg_color.b = bgcolor;

		m_title_size.y = (1.f - m_timer.get_progress()) * m_title->m_size.y;

		break;
	}

	case State::FLIPPING_END: {
		if (m_timer.check()) {
			m_timer.start(500ms);
			m_state = State::INTERVAL;
			m_next_state = State::MOVE;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1s);
			break;
		}

		auto color = static_cast<std::uint8_t>((.5f + (m_timer.get_progress() / 2)) * 255.f);
		SDL_SetTextureColorMod(static_cast<SDL_Texture*>(m_title->data()), color, color, color);

		auto bgcolor = static_cast<std::uint8_t>((1.5f - (m_timer.get_progress() / 2)) * 255.f);
		m_bg_color.r = bgcolor;
		m_bg_color.g = bgcolor;
		m_bg_color.b = bgcolor;

		m_title_size.y = m_timer.get_progress() * m_title->m_size.y;

		break;
	}

	case State::MOVE: {
		if (m_timer.check()) {
			// TODO: End
			m_timer.start(500ms);
			m_state = State::INTERVAL;
			m_next_state = State::SHOW_TEXT;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1s);
			break;
		}

		;
		auto ycenter = static_cast<float>(cog2d::graphics::get_logical_size().y) / 2.f;
		m_y_pos = (ycenter) - (75.f * m_timer.get_progress());

		break;
	}

	case State::SHOW_TEXT: {
		if (m_timer.check()) {
			// TODO: End
			m_cover_width = 0;
			m_timer.start(10s);
			m_state = State::INTERVAL;
			m_next_state = State::FLIPPING_START;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1500ms);
			m_draw_text = true;
		}

		m_cover_width = (1.f - m_timer.get_progress()) * m_text_texture->size().x;

		break;
	}

	default:
		break;
	}
}

void Cog2dIntro::draw()
{
	cog2d::Vector size(cog2d::graphics::get_logical_size());
	//Vector center = {sizef.x / 2.f, sizef.y / 2.f};
	//cog2d::graphics::draw_texture({center, {m_title_size.x, 1.f}}, m_title, 0.f, m_flip);

	cog2d::graphics::draw_rect({{0, 0}, {size.x, size.y}}, true, m_bg_color);

	cog2d::Vector center = {size.x / 2.f, size.y / 2.f};
	cog2d::Vector titlepos = {center.x, m_y_pos};
	cog2d::graphics::draw_texture(m_title.get(), {titlepos - (m_title_size / 2), m_title_size},
	                              m_bg_color.inverted(), m_flip);

	if (m_draw_text) {
		cog2d::Vector texsizef = {static_cast<float>(m_text_texture->size().x),
		                          static_cast<float>(m_text_texture->size().y)};
		cog2d::Vector pos = {center.x - (texsizef.x / 2.f), center.y - (texsizef.y / 2.f) + 20};
		cog2d::graphics::draw_texture(m_text_texture.get(), pos);
		//m_font->write_text(nullptr, m_text, pos);

		cog2d::graphics::draw_rect({{pos.x + (texsizef.x - std::floor(m_cover_width)), pos.y},
		                            {m_cover_width, texsizef.y}},
		                           true, 0xFF000000);
	}

	//cog2d::graphics::draw_point({0, 0}, 0xFF0000FF);
}

bool Cog2dIntro::event(SDL_Event* ev)
{
	return true;
}

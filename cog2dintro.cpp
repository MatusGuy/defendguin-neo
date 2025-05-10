#include "cog2dintro.hpp"

#include <cog2d/util/logger.hpp>
#include <cog2d/video/graphicsengine.hpp>

Cog2dIntro::Cog2dIntro():
	m_title(),
	m_y_pos(0),
	m_title_size(0, 0),
	m_timer(),
	m_state(State::STRETCHING),
	m_next_state(State::INTERVAL),
	m_flip(SDL_FLIP_HORIZONTAL),
	m_bg_color(0xFFFFFFFF),
	m_draw_text(false)
{

}


void Cog2dIntro::init()
{
	COG2D_USE_ASSETMANAGER;

	m_title = assetmanager.pixmaps.load_file("cog2d-ng.png");
	m_title_size = m_title->get_size();
	m_title_size.x = 0;

	COG2D_USE_GRAPHICSENGINE;
	m_y_pos = static_cast<float>(graphicsengine.get_logical_size().y) / 2.f;

	m_font = new cog2d::BitmapFont();
	m_font->set_horizontal_spacing(1);
	m_font->load(cog2d::AssetFile("font.png"));

	SDL_version version;
	SDL_GetVersion(&version);
	m_text = fmt::format("SDL {} {} {}", version.major, version.minor, version.patch);
	m_text_texture = assetmanager.pixmaps.load_file(m_font->create_text(m_text));
	m_cover_width = static_cast<float>(m_text_texture->get_size().x);

	// TODO: abstract this
	//SDL_SetTextureBlendMode(m_title->get_sdl_texture(), SDL_BLENDMODE_ADD);
	SDL_SetTextureColorMod(m_title->to_sdl(), 0, 0, 0);
}

void Cog2dIntro::update()
{
	// TODO: state machine class?
	switch (m_state) {
	case State::STRETCHING:
		if (m_timer.check()) {
			m_state = State::INTERVAL;
			m_next_state = State::FLIPPING_START;
			m_timer.start(500);
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1000);
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
			m_flip = SDL_FLIP_NONE;
			m_state = State::FLIPPING_END;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1000);
			break;
		}

		auto color = static_cast<std::uint8_t>((m_timer.get_progress() / 2) * 255.f);
		SDL_SetTextureColorMod(m_title->to_sdl(), color, color, color);

		auto bgcolor = static_cast<std::uint8_t>((1.f - (m_timer.get_progress() / 2)) * 255.f);
		m_bg_color.r = bgcolor;
		m_bg_color.g = bgcolor;
		m_bg_color.b = bgcolor;

		m_title_size.y = (1.f - m_timer.get_progress()) * m_title->m_size.y;

		break;
	}

	case State::FLIPPING_END: {
		if (m_timer.check()) {
			m_timer.start(500);
			m_state = State::INTERVAL;
			m_next_state = State::MOVE;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1000);
			break;
		}

		auto color = static_cast<std::uint8_t>((.5f + (m_timer.get_progress() / 2)) * 255.f);
		SDL_SetTextureColorMod(m_title->to_sdl(), color, color, color);

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
			m_timer.start(500);
			m_state = State::INTERVAL;
			m_next_state = State::SHOW_TEXT;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1000);
			break;
		}

		COG2D_USE_GRAPHICSENGINE;
		auto ycenter = static_cast<float>(graphicsengine.get_logical_size().y) / 2.f;
		m_y_pos = ycenter - (75.f * m_timer.get_progress());

		break;
	}

	case State::SHOW_TEXT: {
		if (m_timer.check()) {
			// TODO: End
			m_cover_width = 0;
			m_timer.start(10000);
			m_state = State::INTERVAL;
			m_next_state = State::FLIPPING_START;
			break;
		}

		if (!m_timer.started()) {
			m_timer.start(1500);
			m_draw_text = true;
		}

		m_cover_width = (1.f - m_timer.get_progress()) * m_text_texture->get_size().x;

		break;
	}

	default:
		break;
	}
}

void Cog2dIntro::draw()
{
	COG2D_USE_GRAPHICSENGINE;

	const cog2d::Vector_t<int>& size = graphicsengine.get_logical_size();
	cog2d::Vector sizef = {static_cast<float>(size.x), static_cast<float>(size.y)};
	//Vector center = {sizef.x / 2.f, sizef.y / 2.f};
	//graphicsengine.draw_texture({center, {m_title_size.x, 1.f}}, m_title, 0.f, m_flip);

	//*
	graphicsengine.draw_rect({{0,0}, {sizef.x, sizef.y}}, true, m_bg_color);

	cog2d::Vector center = {sizef.x / 2.f, sizef.y / 2.f};
	graphicsengine.draw_texture({{center.x, m_y_pos}, {m_title_size.x, m_title_size.y}}, m_title,
	                            0.f, m_flip);

	if (m_draw_text) {
		cog2d::Vector texsizef = {static_cast<float>(m_text_texture->get_size().x),
		                          static_cast<float>(m_text_texture->get_size().y)};
		cog2d::Vector pos = {center.x - (texsizef.x / 2.f), center.y - (texsizef.y / 2.f) + 20};
		graphicsengine.draw_texture({pos, m_text_texture->get_size()}, m_text_texture);

		graphicsengine.draw_rect({{pos.x + (texsizef.x - std::floor(m_cover_width)), pos.y},
		                          {m_cover_width, texsizef.y}},
		                         true, 0xFF000000);
	}
	//*/

	graphicsengine.draw_point({0,0}, 0xFF0000FF);
}

bool Cog2dIntro::event(SDL_Event* ev)
{
	return true;
}

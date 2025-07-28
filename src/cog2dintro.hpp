#ifndef COG2DINTRO_HPP
#define COG2DINTRO_HPP

#include <cog2d/util/timer.hpp>
#include <cog2d/assets/assetmanager.hpp>
#include <cog2d/video/font/pixmapfont.hpp>
#include <cog2d/screen.hpp>

class Cog2dIntro : public cog2d::Screen
{
public:
	Cog2dIntro();

	void init() override;
	void update() override;
	void draw() override;
	bool event(SDL_Event* ev) override;

private:
	enum State : std::uint8_t {
		STRETCHING,
		INTERVAL,
		FLIPPING_START,
		FLIPPING_END,
		MOVE,
		SHOW_TEXT
	};

private:
	inline bool text_shown() { return m_state == State::SHOW_TEXT || m_cover_width == 0; }

private:
	cog2d::Asset<cog2d::Texture> m_title;
	float m_y_pos;
	cog2d::Vector m_title_size;
	cog2d::Color m_title_color;

	cog2d::Timer m_timer;
	State m_state;
	State m_next_state;
	SDL_RendererFlip m_flip;
	cog2d::Color m_bg_color;

	cog2d::PixmapFont* m_font;
	std::string m_text;
	float m_cover_width;
	bool m_draw_text;

	// FIXME: There should of course be a way to automate the creation of text textures.
	std::unique_ptr<cog2d::Texture> m_text_texture;
};

#endif // COG2DINTRO_HPP

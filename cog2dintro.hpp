#ifndef COG2DINTRO_HPP
#define COG2DINTRO_HPP

#include <timer.hpp>
#include <assetmanager.hpp>
#include <bitmapfont.hpp>

class Cog2dIntro : public Screen
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
	Texture* m_title;
	float m_y_pos;
	Vector m_title_size;
	Timer m_timer;
	State m_state;
	State m_next_state;
	SDL_RendererFlip m_flip;
	Color m_bg_color;

	BitmapFont* m_font;
	std::string m_text;
	Texture* m_text_texture;
	float m_cover_width;
	bool m_draw_text;
};

#endif // COG2DINTRO_HPP

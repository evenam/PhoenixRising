#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(Graphics *g)
{
	gm = g;
	FONT_TITLE = gm->load_font("game_font.ttf", 56);
	IMG_BACKGROUND = gm->load_image("menu.png");
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::draw()
{
	reset_keys();
	gm->draw_image(0,0,IMG_BACKGROUND);
	gm->draw_text(400, 300, FONT_TITLE, "loading...", Graphics::get_color_rgb(255, 0, 0), true);
	gm->draw_text(402, 302, FONT_TITLE, "loading...", Graphics::get_color_rgb(255, 255, 255), true);
	gm->update();
}

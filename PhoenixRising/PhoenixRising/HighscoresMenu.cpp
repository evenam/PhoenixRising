#include "HighscoresMenu.h"

HighscoresMenu::HighscoresMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d)
{
	ks = keystate;
	gm = g;
	gs = s;
	gd = d;

	reset_keys();
}

HighscoresMenu::~HighscoresMenu()
{
}

void HighscoresMenu::update()
{
	if (ks->key_space)
	{
		*gs = GS_MAIN_MENU;
		reset_keys();
	}
}

void HighscoresMenu::draw()
{
	gm->draw_image(0, 0, gd->resources.IMG_BACKGROUND2);

	gm->draw_text(400, 100, gd->resources.FONT_TITLE, "HighScores:", Graphics::get_color_rgb(255, 0, 0), true);
	gm->draw_text(402, 102, gd->resources.FONT_TITLE, "HighScores:", Graphics::get_color_rgb(255, 255, 255), true);

	for (unsigned int i = 0; i < 10; i ++)
	{
		stringstream ss;
		ss.clear();
		ss << gd->highscores.scores[i];
		gm->draw_text(100, 150 + i * 30, gd->resources.FONT_OPTIONS, gd->highscores.names[i], Graphics::get_color_rgb(255, 0, 0), false);
		gm->draw_text(101, 151 + i * 30, gd->resources.FONT_OPTIONS, gd->highscores.names[i], Graphics::get_color_rgb(255, 255, 255), false);

		gm->draw_text(500, 150 + i * 30, gd->resources.FONT_OPTIONS, ss.str(), Graphics::get_color_rgb(255, 0, 0), false);
		gm->draw_text(501, 151 + i * 30, gd->resources.FONT_OPTIONS, ss.str(), Graphics::get_color_rgb(255, 255, 255), false);
	}

	gm->update();
}

void HighscoresMenu::reset()
{
	reset_keys();
}
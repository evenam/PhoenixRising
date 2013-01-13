#include "DifficultyMenu.h"

DifficultyMenu::DifficultyMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d)
{
	ks = keystate;
	gm = g;
	gs = s;
	gd = d;

	option = 0;
	options[0] = "Easy";
	options[1] = "Medium";
	options[2] = "Hard";
}

DifficultyMenu::~DifficultyMenu(void)
{
}

void DifficultyMenu::draw()
{
	gm->draw_image(0, 0, gd->resources.IMG_BACKGROUND2);

	gm->draw_text(400, 100, gd->resources.FONT_TITLE, "Difficulty:", Graphics::get_color_rgb(255, 0, 0), true);
	gm->draw_text(402, 102, gd->resources.FONT_TITLE, "Difficulty:", Graphics::get_color_rgb(255,255,255), true);

	for (int i = 0; i < MAX_OPTIONS; i ++)
	{
		if (i == option)
			gm->draw_text(400,300 + 50 * i,gd->resources.FONT_OPTIONS, options[i], Graphics::get_color_rgb(255, 255, 255), true);
		else
			gm->draw_text(400,300 + 50 * i,gd->resources.FONT_OPTIONS, options[i], Graphics::get_color_rgb(255, 0, 0), true);
	}

	gm->update();
}

void DifficultyMenu::update()
{
	if (ks->key_up)
		option = (option - 1 + MAX_OPTIONS) % MAX_OPTIONS;
	if (ks->key_down)
		option = (option + 1) % MAX_OPTIONS;
	if (ks->key_space)
	{
		gd->difficulty = option;
		*gs = GS_LEVEL;
		gd->level = 0;
	}

	reset_keys();
}

void DifficultyMenu::reset()
{
	option = 0;
	reset_keys();
}
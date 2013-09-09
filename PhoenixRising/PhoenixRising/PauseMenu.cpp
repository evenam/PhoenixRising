#include "PauseMenu.h"

PauseMenu::PauseMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d)
{
	gm = g;
	ks = keystate;
	gs = s;
	gd = d;

	options[0] = "Resume";
	options[1] = "Restart";
	options[2] = "Main Menu";
	options[3] = "Exit";

	option = 0;

	reset_keys();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw()
{
	gm->draw_image(0, 0, gd->resources.IMG_BACKGROUND2);
	gm->draw_text(400, 100, gd->resources.FONT_TITLE, "Pause", Graphics::get_color_rgb(255, 0, 0), true);
	gm->draw_text(402, 102, gd->resources.FONT_TITLE, "Pause", Graphics::get_color_rgb(255, 255, 255), true);

	for (unsigned int i = 0; i < MAX_OPTIONS; i ++)
	{
		if (i == option)
			gm->draw_text(400, 300 + i * 50, gd->resources.FONT_OPTIONS, options[i], Graphics::get_color_rgb(255, 255, 255), true);
		else
			gm->draw_text(400, 300 + i * 50, gd->resources.FONT_OPTIONS, options[i], Graphics::get_color_rgb(255, 0, 0), true);
	}

	gm->update();
}

void PauseMenu::update()
{
	if (ks->key_up)
		option --;
	if (ks->key_down)
		option ++;
	if (ks->key_space)
		execute_option(option);
	if (ks->key_pause)
	{
		option = 0;
		execute_option(option);
	}

	reset_keys();

	while (option >= MAX_OPTIONS)
		option -= MAX_OPTIONS;
	while (option < 0)
		option += MAX_OPTIONS;
}

void PauseMenu::execute_option(int op)
{
	switch (op)
	{
	case 0:
		*gs = GS_LEVEL;
		break;
	case 1:
		*gs = GS_DIFFICULTY;
		gd->level_reset = true;
		gd->level = 0;
		break;
	case 2:
		*gs = GS_MAIN_MENU;
		break;
	case 3:
		*gs = GS_EXIT;
		break;
	}
}

void PauseMenu::reset()
{
	option = 0;
	reset_keys();
}
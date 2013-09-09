#include "MainMenu.h"

MainMenu::MainMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d)
{
	ks = keystate;
	gm = g;
	gs = s;
	gd = d;

	options[0] = "Play";
	options[1] = "Exit";

	option = 0;

	reset_keys();
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw()
{
	gm->draw_image(0, 0, gd->resources.IMG_BACKGROUND3);
	gm->draw_text(400, 100, gd->resources.FONT_TITLE, "Shooter", Graphics::get_color_rgb(255, 0, 0), true);
	gm->draw_text(402, 102, gd->resources.FONT_TITLE, "Shooter", Graphics::get_color_rgb(255, 255, 255), true);

	for (unsigned int i = 0; i < MAX_OPTIONS; i ++)
	{
		if (i == option)
			gm->draw_text(400, 300 + i * 50, gd->resources.FONT_OPTIONS, options[i], Graphics::get_color_rgb(255, 255, 255), true);
		else
			gm->draw_text(400, 300 + i * 50, gd->resources.FONT_OPTIONS, options[i], Graphics::get_color_rgb(255, 0, 0), true);
	}

	gm->update();
}

void MainMenu::update()
{
	if (ks->key_up)
		option --;
	if (ks->key_down)
		option ++;
	if (ks->key_space)
		execute_option(option);
	if (ks->key_pause)
	{
		option = MAX_OPTIONS - 1;
		execute_option(option);
	}

	reset_keys();

	while (option >= MAX_OPTIONS)
		option -= MAX_OPTIONS;
	while (option < 0)
		option += MAX_OPTIONS;

}

void MainMenu::execute_option(int op)
{
	switch (op)
	{
	case 0:
		*gs = GS_DIFFICULTY;
		gd->level = 0;
		gd->level_reset = true;
		break;
	case 1:
		*gs = GS_EXIT;
		break;
	}
}

void MainMenu::reset()
{
	option = 0;
	reset_keys();
}
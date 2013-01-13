#include "EnterNameMenu.h"

EnterNameMenu::EnterNameMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d)
{
	ks = keystate;
	gm = g;
	gs = s;
	gd = d;
	ks->reset();

	name = "";
	pos = 0;
	for (int i = 0; i < 20; i ++)
		vpos[i] = 0;

	charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	reset();
}

EnterNameMenu::~EnterNameMenu()
{
}

void EnterNameMenu::draw()
{
	gm->draw_image(0, 0, gd->resources.IMG_BACKGROUND2);

	gm->draw_text(400, 100, gd->resources.FONT_TITLE, "Enter your name:", Graphics::get_color_rgb(255, 0, 0), true);
	gm->draw_text(402, 102, gd->resources.FONT_TITLE, "Enter your name:", Graphics::get_color_rgb(255,255,255), true);

	for (int i = 0; i < 20; i ++)
	{
		if (pos != i)
			name += charset[vpos[i]];
		else
		{
			name += "[";
			name += charset[vpos[i]];
			name += "]";
		}
	}

	gm->draw_text(400,300,gd->resources.FONT_OPTIONS, name, Graphics::get_color_rgb(255, 255, 255), true);

	gm->update();
}

void EnterNameMenu::update()
{
	name = "";
	
	if (ks->key_space)
	{
		for (int i = 0; i < 20; i ++)
		{
			name += charset[vpos[i]];
		}
		if (name != "                    ")
		{
			string x;
			for (ObjectIndex i = 0; i < name.size(); i ++)
			{
				if (name[i] != ' ')
					x += name[i];
			}
			gd->player_name = x;
			gd->highscores.scores[9] = gd->score;
			gd->highscores.names[9] = gd->player_name;
			gd->refresh_highscores();
			*gs = GS_HIGHSCORE_SHOW;
		}
	}

	if (ks->key_left)
	{
		if (pos > 0)
			pos --;
	}
	if (ks->key_right)
	{
		if (pos < MAX_NAME_SIZE - 1)
			pos ++;
	}
	if (ks->key_up)
	{
		vpos[pos] = (vpos[pos] + 1) % CHAR_UPPER;
	}
	if (ks->key_down)
	{
		vpos[pos] = (vpos[pos] - 1 + CHAR_UPPER) % CHAR_UPPER;
	}
	reset_keys();
}

void EnterNameMenu::reset()
{
	name = "";
	pos = 0;
	for (int i = 0; i < 20; i ++)
		vpos[i] = 0;
	reset_keys();
}
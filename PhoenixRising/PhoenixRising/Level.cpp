#include "Level.h"
#include <windows.h>

Level::Level(string filename, KeyState *keyState, Graphics *g, GameState *s, GameData *d)
{
	ifstream file;
	file.open(filename.c_str());
	srand((unsigned int)time(NULL));
	gm = g;
	gs = s;
	gd = d;
	data_file_name = filename;
	if (file.good())
	{
		string id;
		while (!file.eof())
		{
			file >> id;
			if (id == "player")
			{
				float lparam, rparam;
				file >> lparam >> rparam;
				playerShip = new PlayerShip(keyState, lparam, rparam, 64, 64);
			}
			else if (id == "enemy")
			{
				float param2, param3, param4, param5, param6;
				int param1, param7;
				file >> param1 >> param2 >> param3 >> param4 >> param5 >> param6 >> param7;
				enemyShips.push_back(new EnemyShip((unsigned int)param1, param2, param3, param4, param5, param6, param7, gd->resources.IMG_ENEMY1));
			}
			else if (id == "background_scroll_speed")
			{
				float param;
				file >> param;
				bkg_scroll_spd = param;
			}
		}
		asleep = false;
		bkg_scroll = 0;
		paused = false;
	}
	else
	{
		asleep = true;
	}
	file.close();
}

Level::~Level()
{
	for (unsigned int i = 0; i < enemyShips.size(); i ++)
		delete enemyShips[i];
	for (unsigned int i = 0; i < playerBullets.size(); i ++)
		delete playerBullets[i];
}

void Level::update()
{
	ls = LS_PLAYING;
	playerShip->update();
	if (playerShip->shooting)
	{
		playerBullets.push_back(new PlayerBullet(playerShip->rect->x + 28 - 32, playerShip->rect->y - 20 + 60, 8, 32, -8, 0, 3, gd->resources.IMG_PLAYERBULLET, 0));
		playerBullets.push_back(new PlayerBullet(playerShip->rect->x + 28 + 32, playerShip->rect->y - 20 + 60, 8, 32, -8, 0, 3, gd->resources.IMG_PLAYERBULLET, 180));
		playerBullets.push_back(new PlayerBullet(playerShip->rect->x + 28 - 4, playerShip->rect->y - 20, 8, 32, -8, 0, 3, gd->resources.IMG_PLAYERBULLET, -1));
		playerBullets.push_back(new PlayerBullet(playerShip->rect->x + 28 + 4, playerShip->rect->y - 20, 8, 32, -8, 0, 3, gd->resources.IMG_PLAYERBULLET, -1));
	}

	for (ObjectIndex i = 0; i < enemyShips.size(); i ++)
	{
		enemyShips[i]->update();
		if (enemyShips[i]->shooting)
		{
			enemyBullets.push_back(new EnemyBullet(enemyShips[i]->rect->x + 28, enemyShips[i]->rect->y, 8, 32, 8, 0, 1, gd->resources.IMG_ENEMYBULLET));
		}
	}

	for (ObjectIndex i = 0; i < playerBullets.size(); i ++)
	{
		playerBullets[i]->update();
		for (unsigned int j = 0; j < enemyShips.size(); j ++)
		{
			if ((Rectangle::collision(*enemyShips[j]->rect, *playerBullets[i]->rect)) && (!enemyShips[j]->asleep) && (!playerBullets[i]->asleep))
			{
				enemyShips[j]->hit(playerBullets[i]->getPower());
				playerBullets[i]->asleep = true;
				if (enemyShips[j]->asleep)
					gd->score += 1000;
			}
		}
	}

	for (ObjectIndex i = 0; i < enemyBullets.size(); i ++)
	{
		enemyBullets[i]->update();
		if ((Rectangle::collision(*playerShip->rect, *enemyBullets[i]->rect)) && (!enemyBullets[i]->asleep))
		{
			//playerShip->hit(enemyBullets[i]->getPower());
			enemyBullets[i]->asleep = true;
		}
	}

	// DELETE SCHTUFFZ
	for (vector<PlayerBullet *>::iterator i = playerBullets.begin(); i != playerBullets.end(); /* no condition */)
	{
		if ((* i)->asleep)
		{
			delete (*i);
			i = playerBullets.erase(i);
		}
		else
			i ++;
	}

	for (vector<EnemyShip *>::iterator i = enemyShips.begin(); i != enemyShips.end(); /* no condition */)
	{
		if ((* i)->asleep)
		{
			delete (*i);
			i = enemyShips.erase(i);
		}
		else
			i ++;
	}

	for (vector<EnemyBullet *>::iterator i = enemyBullets.begin(); i != enemyBullets.end(); /* no condition */)
	{
		if ((* i)->asleep)
		{
			delete (*i);
			i = enemyBullets.erase(i);
		}
		else
			i ++;
	}

	paused = playerShip->getKeyState()->key_pause;
	if (paused)
	{
		playerShip->getKeyState()->reset();
		*gs = GS_PAUSE_MENU;
	}

	if (enemyShips.size() < 1)
		ls = LS_DONE_VICTORY;
	else if (playerShip->asleep)
		ls = LS_DONE_DEFEAT;
	if (asleep)
		ls = LS_ERROR;

	if (ls == LS_DONE_VICTORY)
	{
		gd->level ++;
		gd->level_reset = true;
		if (gd->level == MAX_LEVEL)
		{
			gd->level = 0;
			gd->level_reset = true;
			if (gd->score > gd->get_low_highscore())
				*gs = GS_HIGHSCORE_INPUT;
			else
				*gs = GS_HIGHSCORE_SHOW;
		}

		reset_keys();
	}
	else if (ls == LS_DONE_DEFEAT)
	{
		gd->level = 0;
		gd->level_reset = true;
		if (gd->score > gd->get_low_highscore())
				*gs = GS_HIGHSCORE_INPUT;
			else
				*gs = GS_HIGHSCORE_SHOW;
		reset_keys();
	}
}

void Level::draw()
{
	bkg_scroll += bkg_scroll_spd;
	while (bkg_scroll > 600)
		bkg_scroll -= 600;
	while (bkg_scroll < 0)
		bkg_scroll += 600;
	gm->draw_image(0,(int)(-bkg_scroll),gd->resources.IMG_BACKGROUND1);
	gm->draw_image(0,(int)(600-bkg_scroll),gd->resources.IMG_BACKGROUND1);
	gm->draw_image(0,(int)(600+bkg_scroll),gd->resources.IMG_BACKGROUND1);
	gm->draw_image((int)playerShip->rect->x, (int)playerShip->rect->y, gd->resources.IMG_PLAYER);

	for (unsigned int i = 0; i < enemyShips.size(); i ++)
		gm->draw_image((int)enemyShips[i]->rect->x, (int)enemyShips[i]->rect->y, enemyShips[i]->id);

	for (unsigned int i = 0; i < playerBullets.size(); i ++)
		gm->draw_image((int)playerBullets[i]->rect->x, (int)playerBullets[i]->rect->y, playerBullets[i]->id);

	for (unsigned int i = 0; i < enemyBullets.size(); i ++)
		gm->draw_image((int)enemyBullets[i]->rect->x, (int)enemyBullets[i]->rect->y, enemyBullets[i]->id);

	stringstream ss;
	ss << "SCORE: " << gd->score;
	gm->draw_text(10, 560, gd->resources.FONT_OPTIONS, ss.str(), Graphics::get_color_rgb(255, 255, 255), false);

	gm->update();
}

void Level::reset()
{
	KeyState *ks = playerShip->getKeyState();
	delete playerShip;
	for (ObjectIndex i = 0; i < enemyShips.size(); i ++)
		delete enemyShips[i];
	enemyShips.clear();
	for (ObjectIndex i = 0; i < enemyBullets.size(); i ++)
		delete enemyBullets[i];
	enemyBullets.clear();
	for (ObjectIndex i = 0; i < playerBullets.size(); i ++)
		delete playerBullets[i];
	playerBullets.clear();

	ifstream file;
	file.open(data_file_name.c_str());
	srand((unsigned int)time(NULL));
	if (file.good())
	{
		string id;
		while (!file.eof())
		{
			file >> id;
			if (id == "player")
			{
				float lparam, rparam;
				file >> lparam >> rparam;
				playerShip = new PlayerShip(ks, lparam, rparam, 64, 64);
			}
			else if (id == "enemy")
			{
				float param2, param3, param4, param5, param6;
				int param1, param7;
				file >> param1 >> param2 >> param3 >> param4 >> param5 >> param6 >> param7;
				enemyShips.push_back(new EnemyShip((unsigned int)param1, param2, param3, param4, param5, param6, param7, gd->resources.IMG_ENEMY1));
			}
			else if (id == "background_scroll_speed")
			{
				float param;
				file >> param;
				bkg_scroll_spd = param;
			}
		}
		asleep = false;
		bkg_scroll = 0;
		paused = false;
	}
	else
	{
		asleep = true;
	}
	file.close();
}
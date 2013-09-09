#include "Play.h"
#include <iostream>

Play::Play(void)
{
	gm = new Graphics(800, 600, false, "Phoenix Rising");
	ks = new KeyState;
	gs = new GameState;
	gd = new GameData("highscores.dat", "resources.dat");
    
	load_resources();
	loading = new LoadingScreen(gm);
#ifdef _WIN32
    controller = new XboxController(0);
#endif
	*gs = GS_MAIN_MENU;
}

Play::~Play(void)
{
	reset_keys();
	delete gm;
	delete ks;
	delete gs;
	delete gd;
#ifdef _WIN32
	delete controller;
#endif
}

void Play::start()
{
	quit = false;
	Timer fps;

	GameState gs_previous = *gs;
	MainMenu *main_menu = new MainMenu(ks, gm, gs, gd);
	EnterNameMenu *enm = new EnterNameMenu(ks, gm, gs, gd);
	HighscoresMenu *hsm = new HighscoresMenu(ks, gm, gs, gd);
	Level *level1 = new Level("level1.dat", ks, gm, gs, gd);
	Level *level2 = new Level("level2.dat", ks, gm, gs, gd);
	Level *level3 = new Level("level3.dat", ks, gm, gs, gd);
	Level *level4 = new Level("level4.dat", ks, gm, gs, gd);
	Level *level5 = new Level("level5.dat", ks, gm, gs, gd);
	PauseMenu *pause_menu = new PauseMenu(ks, gm, gs, gd);
	DifficultyMenu *dm = new DifficultyMenu(ks, gm, gs, gd);

	gd->level = 0;
	gd->score = 0;

	while (!quit)
	{
		fps.start();

		update();

		gs_previous = *gs;

		switch (*gs)
		{
		case GS_LEVEL:

			Level *level;

			switch (gd->level)
			{
			case 0:
				level = level1;
				break;
			case 1:
				level = level2;
				break;
			case 2:
				level = level3;
				break;
			case 3:
				level = level4;
				break;
			case 4:
				level = level5;
				break;
			}
                
            if (gd->level_reset)
            {
                gd->level_reset = false;
                reset_level(level);
            }

			level->update();
			level->draw();

			break;
		case GS_MAIN_MENU:
			main_menu->update();
			main_menu->draw();
			if (*gs != gs_previous)
			{
				main_menu->reset();
			}
			break;
		case GS_PAUSE_MENU:
			pause_menu->update();
			pause_menu->draw();
			if (*gs != gs_previous)
			{
				pause_menu->reset();
			}
			break;
		case GS_SHOP:
			
			break;
		case GS_HIGHSCORE_INPUT:
			enm->update();
			enm->draw();
			if (*gs != gs_previous)
				enm->reset();
			break;
		case GS_HIGHSCORE_SHOW:
			hsm->update();
			hsm->draw();
			if (*gs != gs_previous)
				hsm->reset();
			break;
		case GS_ENDSEQUENCE:
			
			break;
		case GS_LEVEL_SELECT:
			
			break;
		case GS_CREDITS:
			
			break;
		case GS_DIFFICULTY:
			dm->update();
			dm->draw();
			gd->score = 0;
			if (*gs != gs_previous)
				dm->reset();
			break;
		case GS_EXIT:
			quit = true;
			break;
		}

		if ( fps.get_ticks() < 1000 / FPS )
        {
            SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );
        }

		if ((*gs != gs_previous) && (*gs != GS_EXIT))
			loading->draw();
	}

	delete level1;
	delete level2;
	delete level3;
	delete level4;
	delete level5;

	delete main_menu;
	delete enm;
	delete hsm;
	delete pause_menu;
	delete dm;
}

void Play::update()
{
	SDL_EnableUNICODE(SDL_ENABLE);
	ks->reset();

	while (SDL_PollEvent(&_event_))
	{
		if (_event_.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (_event_.type == SDL_KEYDOWN)
		{
			switch (_event_.key.keysym.sym)
			{
			case SDLK_SPACE:
				ks_kbd.key_space = true;
				break;
			case SDLK_UP:
				ks_kbd.key_up = true;
				break;
			case SDLK_DOWN:
				ks_kbd.key_down = true;
				break;
			case SDLK_LEFT:
				ks_kbd.key_left = true;
				break;
			case SDLK_RIGHT:
				ks_kbd.key_right = true;
				break;
			case SDLK_ESCAPE:
				ks_kbd.key_pause = true;
				break;
			case SDLK_x:
				*gs = GS_EXIT;
				break;
            default:
                break;
			}
		}
		else if (_event_.type == SDL_KEYUP)
		{
			switch (_event_.key.keysym.sym)
			{
			case SDLK_SPACE:
				ks_kbd.key_space = false;
				break;
			case SDLK_UP:
				ks_kbd.key_up = false;
				break;
			case SDLK_DOWN:
				ks_kbd.key_down = false;
				break;
			case SDLK_LEFT:
				ks_kbd.key_left = false;
				break;
			case SDLK_RIGHT:
				ks_kbd.key_right = false;
				break;
			case SDLK_ESCAPE:
				ks_kbd.key_pause = false;
				break;
            default:
                break;
			}
		}
	}
	SDL_EnableUNICODE(SDL_DISABLE);
#ifdef _WIN32
	if (controller->is_connected())
	{
		XboxControllerState *xbcs = controller->get_state();
		if (xbcs->button_a.check_pressed())
		{
			ks_xbc.key_space = true;
		}

		if (xbcs->button_start.check_pressed())
		{
			ks_xbc.key_pause = true;
		}

		if (xbcs->button_up.check_pressed())
		{
			ks_xbc.key_up = true;
		}

		if (xbcs->button_down.check_pressed())
		{
			ks_xbc.key_down = true;
		}

		if (xbcs->button_left.check_pressed())
		{
			ks_xbc.key_left = true;
		}

		if (xbcs->button_right.check_pressed())
		{
			ks_xbc.key_right = true;
		}
		//---------------------------------------------------------
		if (xbcs->button_a.check_released())
		{
			ks_xbc.key_space = false;
		}

		if (xbcs->button_start.check_released())
		{
			ks_xbc.key_pause = false;
		}

		if (xbcs->button_up.check_released())
		{
			ks_xbc.key_up = false;
		}

		if (xbcs->button_down.check_released())
		{
			ks_xbc.key_down = false;
		}

		if (xbcs->button_left.check_released())
		{
			ks_xbc.key_left = false;
		}

		if (xbcs->button_right.check_released())
		{
			ks_xbc.key_right = false;
		}

		// Vibrations
		controller->vibrate(65535 * ((int)controller->get_state()->button_a.check()), 65535 * ((int)controller->get_state()->button_a.check()));
	}

	if (ks_xbc.key_up || ks_kbd.key_up) 
		ks->key_up = true;
	if (ks_xbc.key_down || ks_kbd.key_down)
		ks->key_down = true;
	if (ks_xbc.key_left || ks_kbd.key_left)
		ks->key_left = true;
	if (ks_xbc.key_right || ks_kbd.key_right)
		ks->key_right = true;
	if (ks_xbc.key_pause || ks_kbd.key_pause)
		ks->key_pause = true;
	if (ks_xbc.key_space || ks_kbd.key_space)
		ks->key_space = true;
#else
    
    ks->key_up = ks_kbd.key_up;
    ks->key_down = ks_kbd.key_down;
    ks->key_left = ks_kbd.key_left;
    ks->key_right = ks_kbd.key_right;
    ks->key_pause = ks_kbd.key_pause;
    ks->key_space = ks_kbd.key_space;
    
#endif
    
}

void Play::reset_level(Level *l)
{
	l->reset();
}

void Play::load_resources()
{
	ifstream file;
	file.open(gd->resources.filename.c_str());
	if (file.good())
	{
		string param;
		file >> param;
		gd->resources.IMG_PLAYER = gm->load_image(param);
		file >> param;
		gd->resources.IMG_ENEMY1 = gm->load_image(param);
		file >> param;
		gd->resources.IMG_PLAYERBULLET = gm->load_image(param);
		file >> param;
		gd->resources.IMG_ENEMYBULLET = gm->load_image(param);
		file >> param;		gd->resources.IMG_BACKGROUND1 = gm->load_image(param);
		file >> param;
		gd->resources.IMG_BACKGROUND2 = gm->load_image(param);
		file >> param;
		gd->resources.IMG_BACKGROUND3 = gm->load_image(param);

		int size = 0;
		file >> param >> size;
		gd->resources.FONT_TITLE = gm->load_font(param, size);
		file >> param >> size;
		gd->resources.FONT_OPTIONS = gm->load_font(param, size);
	}
    else
        std::cout << "NO FUCKING FILE IDIOT";
}
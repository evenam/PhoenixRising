#pragma once
#include "DataTypes.h"
#include "SDL.h"
#include "Graphics.h"
#include <vector>
#include "Level.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "LoadingScreen.h"
#include "EnterNameMenu.h"
#include "HighscoresMenu.h"
#include "XboxController.h"
#include "DifficultyMenu.h"
#define FPS 120

using namespace std;

class Play
{
private:
	KeyState *ks;
	Graphics *gm;
	void update();
	SDL_Event _event_;
	bool quit;
	GameState *gs;
	GameData *gd;
	void reset_level(Level *l);
	LoadingScreen *loading;
	XboxController *controller;
	void load_resources();

public:
	Play();
	void start();
	~Play();
};

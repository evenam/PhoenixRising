#pragma once
#include "DataTypes.h"
#include "Graphics.h"
#include <sstream>

class HighscoresMenu : public Manager
{
private:
	KeyState *ks;
	Graphics *gm;
public:
	void update();
	void draw();
	void reset();

	HighscoresMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d);
	~HighscoresMenu();
};

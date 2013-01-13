#pragma once
#include "DataTypes.h"
#include "Graphics.h"

class DifficultyMenu : public Manager
{
private:
	Graphics *gm;
	KeyState *ks;

	int option;
	string options[3];
	static const int MAX_OPTIONS = 3;
public:
	DifficultyMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d);
	~DifficultyMenu();

	void update();
	void draw();
	void reset();
};

#pragma once
#include "DataTypes.h"
#include "Graphics.h"

class PauseMenu : public Manager
{
private:
	Graphics *gm;
	KeyState *ks;

	int option;
	string options[4];
	static const int MAX_OPTIONS = 3;//static const int MAX_OPTIONS = 4;
	void execute_option(int op);
public:
	PauseMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d);
	~PauseMenu();

	void update();
	void draw();
	void reset();
};

#pragma once
#include "DataTypes.h"
#include "Graphics.h"

using namespace std;

class MainMenu : public Manager
{
private:
	KeyState *ks;
	Graphics *gm;

	int option;
	string options[2];
	static const int MAX_OPTIONS = 2;
	void execute_option(int op);
public:
	void update();
	void draw();
	void reset();

	MainMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d);
	~MainMenu();
};

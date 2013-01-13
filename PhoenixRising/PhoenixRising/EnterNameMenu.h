#pragma once
#include "Graphics.h"
#include "DataTypes.h"
#include <string>

using namespace std;

class EnterNameMenu : public Manager
{
private:
	KeyState *ks;
	Graphics *gm;

	int pos, vpos[20];
	static const int CHAR_UPPER = 63;
	string charset;

	static const int MAX_NAME_SIZE = 20;
public:
	EnterNameMenu(KeyState *keystate, Graphics *g, GameState *s, GameData *d);
	~EnterNameMenu();

	void update();
	void draw();
	
	string name;
	void reset();
};

#pragma once
#include "Graphics.h"
#include "DataTypes.h"

class LoadingScreen
{
private:
	Graphics *gm;
	FontIndex FONT_TITLE;
	SpriteIndex IMG_BACKGROUND;
public:
	LoadingScreen(Graphics *g);
	~LoadingScreen();

	void draw();
};

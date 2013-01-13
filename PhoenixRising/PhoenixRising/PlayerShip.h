#pragma once
#include "DataTypes.h"
#include <cmath>

class PlayerShip : public GameObject
{
private:
	KeyState *ks;
	SpriteIndex sprite_index;
	int bulletTimer;

	float hspeed, vspeed;
	
public:
	Rectangle *rect;
	bool shooting;
	virtual void update();
	KeyState *getKeyState();
	PlayerShip();
	PlayerShip(KeyState *keystate, float X, float Y, float W, float H);
	~PlayerShip();
};

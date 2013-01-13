#pragma once
#include "DataTypes.h"
#include <cmath>

class PlayerBullet : public GameObject
{
private:
	float vspeed;
	float hspeed;
	int power;
	int direction;
public:
	int id;
	Rectangle *rect;
	int getPower();
	PlayerBullet(void);
	PlayerBullet(float x, float y, float w, float h, float vspd, float hspd, int pwr, int ident,int dir);
	void update();
	~PlayerBullet(void);
};

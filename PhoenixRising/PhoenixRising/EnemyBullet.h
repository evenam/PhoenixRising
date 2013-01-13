#pragma once
#include "DataTypes.h"

class EnemyBullet : public GameObject
{
protected:
	float vspeed;
	float hspeed;
	int power;
public:
	int id;
	Rectangle *rect;
	int getPower();
	EnemyBullet(void);
	EnemyBullet(float x, float y, float w, float h, float vspd, float hspd, int pwr, int ident);
	void update();
	~EnemyBullet(void);
};

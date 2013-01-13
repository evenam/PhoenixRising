#pragma once
#include "DataTypes.h"

class EnemyShip : public GameObject
{
protected:
	SpriteIndex sprite_index;
	vector<Rectangle *> path_index;
	float way_x, way_y;
	int way_index;
	int shot_timer;
	int hp;
	float speed;
public:
	int id;
	Rectangle *rect;
	bool shooting;
	virtual void update();
	void hit(int power);
	EnemyShip(PathIndex p, float x, float y, float w, float h, float spd, int health, int ident);
	~EnemyShip(void);
};


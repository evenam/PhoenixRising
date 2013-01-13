#include "EnemyShip.h"

EnemyShip::EnemyShip(PathIndex p, float x, float y, float w, float h, float spd, int health, int ident)
{
	rect = new Rectangle(x, y, w, h);
	asleep = false;
	path_index = getEnemyPath(p);
	way_x = rect->x + path_index[0]->x;
	way_y = rect->y + path_index[0]->y;
	way_index = 0;
	hp = health;
	shot_timer = rand() % 200 + 100;
	shooting = false;
	id = ident;
	speed = spd;
}

EnemyShip::~EnemyShip(void)
{
	delete rect;
	for (unsigned int i = 0; i < path_index.size(); i ++)
		delete path_index[i];
}

void EnemyShip::update()
{
	if (shooting = true)
		shooting = false;

	if (shot_timer > 0)
		shot_timer --;

	if (shot_timer == 0)
	{
		shooting = true;
		shot_timer += 200 + rand() % 200;
	}

	if (abs((int)(rect->x - way_x)) < 1)
		rect->x = way_x;
	else
		rect->x -= (abs((int)(rect->x - way_x))/(rect->x - way_x)) * speed;

	if (abs((int)(rect->y - way_y)) < 1)
		rect->y = way_y;
	else
		rect->y -= (abs((int)(rect->y - way_y))/(rect->y - way_y)) * speed;

	if ((rect->x == way_x) && (way_y == rect->y))
	{
		way_index = (++way_index) % path_index.size();
		way_x += path_index[way_index]->x;
		way_y += path_index[way_index]->y;
	}
}

void EnemyShip::hit(int power)
{
	hp -= power;
	if (hp <= 0)
	{
		asleep = true;
	}
}
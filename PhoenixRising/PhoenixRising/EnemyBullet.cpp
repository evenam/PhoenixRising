#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(void)
{
	rect = new Rectangle;
	asleep = false;
	power = 1;
}

EnemyBullet::EnemyBullet(float x, float y, float w, float h, float vspd, float hspd, int pwr, int ident)
{
	rect = new Rectangle(x, y, w, h);
	vspeed = vspd;
	hspeed = hspd;
	asleep = false;
	power = pwr;
	id = ident;
}

EnemyBullet::~EnemyBullet(void)
{
	delete rect;
}

void EnemyBullet::update()
{
	rect->y += vspeed;
	rect->x += hspeed;
	if (rect->y > 600)
		asleep = true;
	if (rect->x > 800)
		asleep = true;
	if (rect->y < 0)
		asleep = true;
	if (rect->x < 0)
		asleep = true;
}

int EnemyBullet::getPower()
{
	return power;
}
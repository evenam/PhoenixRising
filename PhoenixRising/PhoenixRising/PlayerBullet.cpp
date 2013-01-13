#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(void)
{
	rect = new Rectangle;
	asleep = false;
	power = 2;
}

PlayerBullet::PlayerBullet(float x, float y, float w, float h, float vspd, float hspd, int pwr, int ident, int dir)
{
	rect = new Rectangle(x, y, w, h);
	vspeed = vspd;
	hspeed = hspd;
	asleep = false;
	power = pwr;
	id = ident;
	direction = dir;
}

PlayerBullet::~PlayerBullet(void)
{
	delete rect;
}

void PlayerBullet::update()
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

	if (direction != -1)
	{
		hspeed = cos(3.141592654 * direction / 180) * 4;
		direction = (direction + 5) % 360;
	}
}

int PlayerBullet::getPower()
{
	return power;
}
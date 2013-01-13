#include "PlayerShip.h"

PlayerShip::PlayerShip(void)
{
	ks = NULL;
	rect = new Rectangle;
	shooting = false;
	bulletTimer = 0;
	asleep = false;
	hspeed = 0;
	vspeed = 0;
}

PlayerShip::PlayerShip(KeyState *keystate, float X, float Y, float W, float H)
{
	ks = keystate;
	rect = new Rectangle(X,Y,W,H);
	shooting = false;
	bulletTimer = 0;
	asleep = false;
	hspeed = 0;
	vspeed = 0;
}

PlayerShip::~PlayerShip(void)
{
	delete rect;
}

void PlayerShip::update()
{
	// GUN
	if (bulletTimer > 0)
		bulletTimer --;

	if ((ks->key_space) && (bulletTimer == 0))
	{
		bulletTimer = 20;
		shooting = true;
	}
	else
	{
		shooting = false;
	}

	// MOVEMENT
	float xvec, yvec;
	float max_vspeed, max_hspeed;

	if (ks->key_up)
	{
		if (((ks->key_left) && (!ks->key_right)) || ((ks->key_right) && (!ks->key_left)))
		{
			max_vspeed = (float)(-sqrt(2.0) / 2.0);
		}
		else
		{
			max_vspeed = -1;
		}

		vspeed -= 0.1f;

		if (vspeed < max_vspeed)
			vspeed = max_vspeed;
	}
	if (ks->key_down)
	{
		if (((ks->key_left) && (!ks->key_right)) || ((ks->key_right) && (!ks->key_left)))
		{
			max_vspeed = (float)(sqrt(2.0) / 2.0);
		}
		else
		{
			max_vspeed = 1;
		}

		vspeed += 0.1f;

		if (vspeed > max_vspeed)
			vspeed = max_vspeed;
		
	}
	if (ks->key_left)
	{
		if (((ks->key_up) && (!ks->key_down)) || ((ks->key_up) && (!ks->key_down)))
		{
			max_hspeed = (float)(-sqrt(2.0) / 2.0);
		}
		else
		{
			max_hspeed = -1;
		}

		hspeed -= 0.1f;

		if (hspeed < max_hspeed)
			hspeed = max_hspeed;
	}
	if (ks->key_right)
	{
		if (((ks->key_up) && (!ks->key_down)) || ((ks->key_up) && (!ks->key_down)))
		{
			max_hspeed = (float)(sqrt(2.0) / 2.0);
		}
		else
		{
			max_hspeed = 1;
		}

		hspeed += 0.1f;

		if (hspeed > max_hspeed)
			hspeed = max_hspeed;
	}

	xvec = hspeed * 5;
	yvec = vspeed * 5;
	rect->x += xvec;
	rect->y += yvec;

	if (vspeed > 0.05)
		vspeed -= 0.05f;
	else if (vspeed < -0.05)
		vspeed += 0.05f;
	else
		vspeed = 0;

	if (hspeed > 0.05)
		hspeed -= 0.05f;
	else if (hspeed < -0.05)
		hspeed += 0.05f;
	else
		hspeed = 0;

	if (rect->x < 0)
		rect->x = 0;
	if ((rect->x + rect->w) > 800)
		rect->x = 800 - rect->w;
	
	if (rect->y < 300)
		rect->y = 300;
	if ((rect->y + rect->h) > 600)
		rect->y = 600 - rect->h;
}

KeyState *PlayerShip::getKeyState()
{
	return ks;
}
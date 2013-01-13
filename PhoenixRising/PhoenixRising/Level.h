#pragma once
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "DataTypes.h"
#include "Graphics.h"
#include <sstream>

using namespace std;

class Level : public Manager
{
private:
	float bkg_scroll;
	float bkg_scroll_spd;
	Graphics *gm;
public:
	PlayerShip* playerShip;
	vector<EnemyShip *> enemyShips;
	vector<PlayerBullet *> playerBullets;
	vector<EnemyBullet *> enemyBullets;

	void update();
	void draw();
	void reset();

	bool asleep;
	bool paused;
	LevelState ls;
	string data_file_name;

	Level(string filename, KeyState *keyState, Graphics *g, GameState *s, GameData *d);
	~Level();
};

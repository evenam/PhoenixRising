#pragma once

#ifdef _WIN32
    #include "SDL.h"
#else
    #include "SDL/SDL.h"
#endif

#include <vector>
#include <fstream>
#include <string>

using namespace std;

#define MAX_LEVEL 5

typedef unsigned int ObjectIndex;
typedef unsigned int SpriteIndex;
typedef unsigned int PathIndex;
typedef unsigned int FontIndex;
typedef unsigned int LevelNumber;

enum GameState 
{
	GS_LEVEL,
	GS_MAIN_MENU,
	GS_PAUSE_MENU,
	GS_SHOP,
	GS_HIGHSCORE_INPUT,
	GS_HIGHSCORE_SHOW,
	GS_ENDSEQUENCE,
	GS_LEVEL_SELECT,
	GS_CREDITS,
	GS_DIFFICULTY,
	GS_EXIT,
};

enum LevelState
{
	LS_ERROR,
	LS_DONE_VICTORY,
	LS_DONE_DEFEAT,
	LS_PLAYING,
};

class GameData
{
public:
	LevelNumber level;
	long score;
	int cash;
	string player_name;
	bool level_reset;
	int difficulty;

	struct Recources
	{
		string filename;

		SpriteIndex IMG_PLAYER;
		SpriteIndex IMG_ENEMY1;
		SpriteIndex IMG_PLAYERBULLET;
		SpriteIndex IMG_ENEMYBULLET;
		SpriteIndex IMG_BACKGROUND1;
		SpriteIndex IMG_BACKGROUND2;
		SpriteIndex IMG_BACKGROUND3;
		
		FontIndex FONT_TITLE;
		FontIndex FONT_OPTIONS;
	} 
	resources;

	void load_resources();

	struct HighScores
	{
		string filename;
		string names[10];
		long scores[10];
	} 
	highscores;

	void reset();
	void load_highscores();
	void save_highscores();

	void refresh_highscores();
	long get_low_highscore();
	string get_low_highname();

	GameData(string highscore_filename, string resource_filename);
	~GameData();
};

class GameObject
{
public:
	virtual void update() = 0;
	bool asleep;
};

class Manager
{
protected:
	GameState *gs;
	GameData *gd;
public:
	GameState *getGameState() { return gs; };
	GameData *getGameData() { return gd; };
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void reset() = 0;
};

class KeyState
{
public:
	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool key_space;
	bool key_pause;

	KeyState();
	void reset();
};

class Rectangle
{
public:
	Rectangle();
	Rectangle(float X, float Y, float W, float H);
	~Rectangle();

	float x, y, w, h;

	SDL_Rect getSDLRect();

	static bool collision(Rectangle r1, Rectangle r2);
};

class Timer
{
private:
    int startTicks;
    
    int pausedTicks;
    
    bool paused;
    bool started;
    
public:
    Timer();
    
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    
    bool is_started();
    bool is_paused();    
};

template <class T> 
	T *getTypecastedObject(GameObject *object);

vector<Rectangle *> getEnemyPath(PathIndex index);

GameData *load_data(string filename);
void save_data(GameData *gd);

extern KeyState ks_xbc, ks_kbd;
void reset_keys();
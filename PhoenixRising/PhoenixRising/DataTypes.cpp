#include "DataTypes.h"

KeyState::KeyState()
{
	key_up = false;
	key_down = false;
	key_left = false;
	key_right = false;
	key_space = false;
	key_pause = false;
}

void KeyState::reset()
{
	key_up = false;
	key_down = false;
	key_left = false;
	key_right = false;
	key_space = false;
	key_pause = false;
}

Rectangle::Rectangle()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rectangle::Rectangle(float X, float Y, float W, float H)
{
	x = X;
	y = Y;
	w = W;
	h = H;
}

Rectangle::~Rectangle()
{
}

SDL_Rect Rectangle::getSDLRect()
{
	SDL_Rect r;
	r.h = (int)h;
	r.w = (int)w;
	r.x = (int)x;
	r.y = (int)y;

	return r;
}

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;    
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();    
}

void Timer::stop()
{
    started = false;
    paused = false;    
}

int Timer::get_ticks()
{
    if( started == true )
    {
        if( paused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }    
    }
    return 0;    
}

void Timer::pause()
{	
    if( ( started == true ) && ( paused == false ) )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if( paused == true )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

bool Timer::is_started()
{
    return started;    
}

bool Timer::is_paused()
{
    return paused;    
}

bool Rectangle::collision(Rectangle r1, Rectangle r2)
{
	float	r1top = r1.y,			r2top = r2.y;
	float	r1bot = r1.y + r1.h,	r2bot = r2.y + r2.h;
	float	r1lef = r1.x,			r2lef = r2.x;
	float	r1rig = r1.x + r1.w,	r2rig = r2.x + r2.w;

	if (r1top > r2bot)
		return false;
	if (r2top > r1bot)
		return false;
	if (r1lef > r2rig)
		return false;
	if (r2lef > r1rig)
		return false;

	return true;
}

template <class T> 
T *getTypecastedObject(GameObject *object)
{
	return (T*)object;
}

vector <Rectangle *> getEnemyPath(PathIndex index)
{
	vector<Rectangle *> path;
	switch (index)
	{
	case 0: // SQUARE
		path.push_back(new Rectangle(0,64,0,0));
		path.push_back(new Rectangle(64,0,0,0));
		path.push_back(new Rectangle(0,-64,0,0));
		path.push_back(new Rectangle(-64,0,0,0));
		break;
	case 1: // OCTAGON
		path.push_back(new Rectangle(32,0,0,0));
		path.push_back(new Rectangle(16,16,0,0));
		path.push_back(new Rectangle(0,32,0,0));
		path.push_back(new Rectangle(-16,16,0,0));
		path.push_back(new Rectangle(-32,0,0,0));
		path.push_back(new Rectangle(-16,-16,0,0));
		path.push_back(new Rectangle(0,-32,0,0));
		path.push_back(new Rectangle(16,-16,0,0));
		break;
	case 2: // X-SHAPE
		path.push_back(new Rectangle(64,64,0,0));
		path.push_back(new Rectangle(0,-64,0,0));
		path.push_back(new Rectangle(-64,64,0,0));
		path.push_back(new Rectangle(0,-64,0,0));
		break;
	case 3: // REVERSE SQUARE
		path.push_back(new Rectangle(0,64,0,0));
		path.push_back(new Rectangle(-64,0,0,0));
		path.push_back(new Rectangle(0,-64,0,0));
		path.push_back(new Rectangle(64,0,0,0));
		break;
	default:
		path.push_back(new Rectangle(0,0,0,0));
		break;
	}
	return path;
}

void GameData::reset()
{
	level = 0;
	score = 0;
	cash = 0;
	player_name = "";
	level_reset = false;
}

GameData::GameData(string highscore_filename, string resource_filename)
{
	level = 0;
	score = 0;
	cash = 0;
	player_name = "";
	level_reset = false;
	highscores.filename = highscore_filename;
	load_highscores();
	resources.filename = resource_filename;
	//load_resources();
}

GameData::~GameData()
{
	save_highscores();
}

void GameData::load_highscores()
{
	ifstream file;
	file.open(highscores.filename.c_str());
	if (file.good())
	{
		for (unsigned int i = 0; i < 10; i ++)
		{
			file >> highscores.names[i];
			file >> highscores.scores[i];
		}
	}
	file.close();
}

void GameData::save_highscores()
{
	ofstream file;
	file.open(highscores.filename.c_str());
	if (file.good())
	{
		for (unsigned int i = 0; i < 10; i ++)
		{
			file << highscores.names[i] << " ";
			file << highscores.scores[i] << "\n";
		}
	}
	file.close();
}

KeyState ks_kbd = KeyState();
KeyState ks_xbc = KeyState();

void reset_keys()
{
	ks_kbd.reset();
	ks_xbc.reset();
}

long GameData::get_low_highscore()
{
	return highscores.scores[9];
}

string GameData::get_low_highname()
{
	return highscores.names[9];
}

void GameData::refresh_highscores()
{
	string temp = highscores.names[9];
	long temp2 = highscores.scores[9];

	int i = 8;

	while (highscores.scores[i] < temp2 && i >= 0)
	{
		if (i >= 0)
		{
			highscores.scores[i + 1] = highscores.scores[i];
			highscores.names[i + 1] = highscores.names[i];
			i --;
		}
		else
		{
			i --;
		}
	}

	highscores.scores[i + 1] = temp2;
	highscores.names[i + 1] = temp;
}

/*void GameData::load_resources()
{
	ifstream file;
	file.open(resources.filename);
	file >> resources.IMG_PLAYER;
}*/
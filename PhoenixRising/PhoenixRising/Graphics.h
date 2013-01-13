#pragma once

#include "SDL.h"
#include <string>
#include <vector>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "DataTypes.h"

using namespace std;

class Graphics
{
private:
	SDL_Surface* screen;
	vector <SDL_Surface*> gfx;
	vector <TTF_Font *> fonts;
public:
	SDL_Surface* get_screen();
	Graphics(int width, int height, bool fs, const char *title);
	~Graphics();
	SpriteIndex load_image(std::string filename);
	SDL_Surface* get_image(SpriteIndex image_index);
	void draw_image(int x, int y, SpriteIndex index, SDL_Rect* part = NULL);
	FontIndex load_font(string filename, int size);
	TTF_Font* get_font(FontIndex index);
	void draw_text(int x, int y, FontIndex index, string text, SDL_Color color, bool center);
	static SDL_Color get_color_rgb(int r, int g, int b);
	void update();
	void set_new_video_mode(int w, int h, bool fs, const char *title);
};


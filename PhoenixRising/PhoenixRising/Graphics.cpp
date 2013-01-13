#include "Graphics.h"

Graphics::Graphics(int width, int height, bool fs, const char *title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	screen = SDL_SetVideoMode(width, height, 32, fs?(SDL_SWSURFACE | SDL_FULLSCREEN):SDL_SWSURFACE);
	SDL_WM_SetCaption(title, NULL);
}

Graphics::~Graphics(void)
{
	for (SpriteIndex i = 0; i < gfx.size(); i ++)
		SDL_FreeSurface(gfx[i]);
	for (FontIndex i = 0; i < fonts.size(); i ++)
		TTF_CloseFont(fonts[i]);
	TTF_Quit();
	SDL_Quit();
}

SpriteIndex Graphics::load_image(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    gfx.push_back(optimizedImage);
	return (gfx.size() - 1);
}

SDL_Surface *Graphics::get_screen()
{
	return screen;
}

SDL_Surface *Graphics::get_image(SpriteIndex image_index)
{
	return gfx[image_index];
}

void Graphics::draw_image(int x, int y, SpriteIndex index, SDL_Rect* part)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( gfx[index], part, screen, &offset );
}

void Graphics::update()
{
	SDL_Flip(screen);
}

FontIndex Graphics::load_font(string filename, int size)
{
	TTF_Font *f = NULL;
	f = TTF_OpenFont(filename.c_str(), size);
	fonts.push_back( f );
	return (fonts.size() - 1);
}

TTF_Font* Graphics::get_font(FontIndex index)
{
	return fonts[index];
}

void Graphics::draw_text(int x, int y, FontIndex index, string text, SDL_Color color, bool center)
{
	SDL_Surface *s;
	s = TTF_RenderText_Solid(fonts[index], text.c_str(), color);
	if (s != NULL)
	{
		gfx.push_back(s);
		if (center)
		{
			draw_image(x - s->w / 2, y - s->h / 2, gfx.size() - 1);
		}
		else
		{
			draw_image(x, y, gfx.size() - 1);
		}
		
		gfx.pop_back();
		SDL_FreeSurface(s);
	}
}

SDL_Color Graphics::get_color_rgb(int r, int g, int b)
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

void Graphics::set_new_video_mode(int w, int h, bool fs, const char *title)
{
	SDL_FreeSurface(screen);
	screen = SDL_SetVideoMode(w, h, 32, ((fs)?(SDL_SWSURFACE | SDL_FULLSCREEN):(SDL_SWSURFACE)));
	SDL_WM_SetCaption(title, NULL);
}
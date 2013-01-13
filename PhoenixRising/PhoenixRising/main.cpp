#include "Play.h"

Play *game;

int main(int argc, char **argv)
{
	game = new Play();

	game->start();

	delete game;

	return 0;
}
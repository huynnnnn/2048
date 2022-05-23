#pragma once
#include "Board.h"
#include "move.h"
#include "Music.h"

class Game 
{
public:
    Game();
    ~Game();
    bool initialize();
    bool init();
    bool initTexture();
    void setColor();
    void freeSpace();
    void gameLoop();
    void create();
    void move(SDL_Event event, int **&tab, int size, int **&backtab, unsigned int &score, unsigned int &backScore);
    void render();
    void gameStart();
    SDL_Surface* loadSurface( std::string path );
    bool loadMedia( std::string path );
    void loadIMG( std::string path );
    void close();

private:
    int size = 3;
	bool getStart = 0;
	unsigned int score = 0;
    unsigned int backScore = score;
	int showSize = 0;
	int** tab;
	int** backtab;
	int fileSize = 0;

	int t1, t2, quit = 0, rc;
	double delta, worldTime = 0;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
    SDL_Surface* gPNGSurface;

    char text[128];

    int black;
    int rose;

    Mus* mus;
};
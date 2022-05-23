#include "Game.h"

Game::Game() {}
Game::~Game() {}

//chọn hướng
void Game::move(SDL_Event event, int **&tab, int size, int **&backtab, unsigned int &score, unsigned int &backScore) {
	int **checkTab = createtab(size);
	int checkScore = backScore;
	copyTab(checkTab, backtab, size);

	copyTab(backtab, tab, size);
	backScore = score;
	
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            moveTop(tab, size, score);
            break;
        case SDLK_DOWN:
            moveBot(tab, size, score);
            break;
        case SDLK_LEFT:
            moveLeft(tab, size, score);
            break;
        case SDLK_RIGHT:
            moveRight(tab, size, score);
            break;
    }

	if (checkToRandom(tab, backtab, size)) {
		randomOnBoard(tab, size);
	}
	else {
		copyTab(backtab, checkTab, size);
		backScore = checkScore;
	}

	for (int i = 0; i < size; ++i)
		delete[] checkTab[i];
	delete[] checkTab;
}

bool Game::initialize() {
    bool sucsess = true;
    if (!init())
        sucsess = false;
    if (!initTexture()) 
        sucsess = false;
    setColor();
    return sucsess;
}

bool Game::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return false;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return false;
	};

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "2048");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    return true;
}

bool Game::initTexture() {
    charset = SDL_LoadBMP("./img/cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return false;
	};
	SDL_SetColorKey(charset, true, 0x000000);
    return true;
}

void Game::setColor() {
    black = SDL_MapRGB(screen->format, 0, 0, 0);
	rose = SDL_MapRGB(screen->format, 236, 121, 133);
}

void Game::create() {
    mus = new Mus();
    tab = createtab(size);
	backtab = createtab(size);
	copyTab(tab, backtab, size);	
}

void Game::freeSpace() {
    //xoa bo nho
	for (int i = 0; i < size; ++i)
		delete[] tab[i];
	delete[] tab;

	for (int i = 0; i < size; ++i)
		delete[] backtab[i];
	delete[] backtab;

	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Game::render() {
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Game::gameStart() {
    loadIMG("./img/background.png");
    mus->getMus("./music/reload.wav");
    if (size >= 10) size = 10;
    if (size <= 3) size = 3;

    DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, rose);
    sprintf(text, "Choose size of map: \030 - Bigger, \031 - Smaller Enter - accept");
    DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 18, text, charset);

    DrawRectangle(screen, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 36, 200, 36, black, rose);
    sprintf(text, "Size: %d", size);
    DrawString(screen, SCREEN_WIDTH/2  -  strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
            else if (event.key.keysym.sym == SDLK_UP) size++;
            else if (event.key.keysym.sym == SDLK_DOWN) size--;
            else if (event.key.keysym.sym == SDLK_RETURN) { 
                getStart = 1; 
                Mix_HaltMusic();
                tab = createtab(size);
                backtab = createtab(size);
                copyTab(tab, backtab, size);
                t1 = SDL_GetTicks();
                backScore = 0;
                score = 0;
                worldTime = 0;
            }
            break;
        case SDL_QUIT:
            quit = 1;
            break;
        };
    };
    render();
    close();
}

void Game::gameLoop() {
    while(!quit) {

		//hiển thị cửa sổ, chọn kích thước
		if (!getStart) 
		    gameStart();
		//hiển thị game
		else if(getStart && !checkLose(tab, size) && !checkWin(tab, size)){
            loadIMG("./img/bgr.png");
            mus->getMus("./music/lose.wav");
			//tinh thoi gian
			t2 = SDL_GetTicks();
			delta = (t2 - t1) * 0.001;
			t1 = t2;
			worldTime += delta;



			DrawBoard(screen, tab, size, black, rose, charset);
			DrawScore(screen, score, charset);
		
			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, rose);
			sprintf(text, "Time = %.1lf s  ", worldTime);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			sprintf(text, "Esc - Exit, Arrows - Move, u - Back move, n - New game");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			render();

			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                quit = 1;
                                break;
                            case SDLK_u:
                                copyTab(tab, backtab, size); 
							    score = backScore;
                                break;
                            case SDLK_n:
                                for (int i = 0; i < size; ++i)
                                    delete[] tab[i];
                                delete[] tab;

                                for (int i = 0; i < size; ++i)
                                    delete[] backtab[i];
                                delete[] backtab;
                                getStart = 0; 
                                break;
                            default:
                                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
                                    move(event, tab, size, backtab, score, backScore);
                                break;
                        }
						break;
					case SDL_QUIT:
						quit = 1;
						break;
				};
			};
            close();
		}
		//kiểm tra nếu ng chơi thua/ thắng
		else if (checkLose(tab, size)) {
            loadIMG("./img/loseCat.jpg");
			double endTime = worldTime;
			while (!quit) {
				// SDL_FillRect(screen, NULL, black);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, rose);
				sprintf(text, "You Lose: esc - quit");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 18, text, charset);

				DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, black, rose);
				sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, score);
				DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};

				render();
                close();
			}
		}
		else if (checkWin(tab, size)) {
            loadIMG("./img/winCat.jpg");
			double endTime = worldTime;
			while (!quit) {
				// SDL_FillRect(screen, NULL, black);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, rose);
				sprintf(text, "You Win: esc -  to quit");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 18, text, charset);

				DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, black, rose);
				sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, score);
				DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) 
							quit = 1;
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};

				render();
                close();
			}
		}
	};
    mus->freeMus();
}

SDL_Surface* Game::loadSurface( std::string path )
{
    SDL_Surface* optimizedSurface = NULL;

    //load anh
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

bool Game::loadMedia( std::string path )
{
	bool success = true;
	gPNGSurface = loadSurface( path );
	if( gPNGSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
	}

	return success;
}

void Game::loadIMG( std::string path ) {
    if( !loadMedia( path ) )
        printf( "Failed to load media!\n" );
    else {
        //Apply the PNG image
        SDL_BlitSurface( gPNGSurface, NULL, screen, NULL );
        //Update the surface
        SDL_UpdateWindowSurface( window );
    }
}

void Game::close() {
    SDL_FreeSurface( gPNGSurface );
    gPNGSurface = NULL;
}
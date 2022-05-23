#include "Music.h"

Mus::Mus() {}

Mus::~Mus() {}

bool Mus::loadMus(std::string path) {
    bool success = true;
    gMusic = Mix_LoadMUS( path.c_str() );
	if( gMusic == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
    return success;
}

void Mus::getMus(std::string path) {
    if (!loadMus(path))
        printf("cannot load music");
    else if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( gMusic, -1 );
    }
}

void Mus::freeMus() {
    Mix_FreeMusic( gMusic );
	gMusic = NULL;
}

#pragma once
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define _USE_MATH_DEFINES

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define BOARD_WIDTH		300
#define BOARD_X 50
#define BOARD_Y 10

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void DrawPoint(SDL_Surface *screen, int X, int Y, int width, const char *number, SDL_Surface *charset);
void DrawBoard(SDL_Surface *screen, int **tab, int size, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *charset);
void DrawScore(SDL_Surface *screen, unsigned int score, SDL_Surface *charset);

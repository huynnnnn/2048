#pragma once
#include "Function.h"

//move points in any direction
void rushTop(int **&tab, int size);
void rushBot(int **&tab, int size);
void rushRight(int **&tab, int size);
void rushLeft(int **&tab, int size);
void moveTop(int **&tab, int size, unsigned int &score);
void moveBot(int **&tab, int size, unsigned int &score);
void moveRight(int **&tab,int size, unsigned int &score);
void moveLeft(int **&tab, int size, unsigned int &score);
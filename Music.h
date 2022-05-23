#pragma once
#include "Function.h"

class Mus
{
public:
    Mus();
    ~Mus();
    bool loadMus(std::string path);
    void getMus(std::string path);
    void freeMus();

private:
    Mix_Music *gMusic;
};
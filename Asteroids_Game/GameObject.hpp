#include <SDL.h>
#include <math.h>
#define PI 3.14159265
#pragma once
using namespace std;

class GameObject
{
    public:
        virtual void draw();
        virtual void update();
        virtual void InputHandle(SDL_Event e);
};
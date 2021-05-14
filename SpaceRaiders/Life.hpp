#include<SDL.h>
#include<iostream>
#pragma once

class Life
{
    private:
        SDL_Renderer * gRenderer = NULL;
        SDL_Texture * asset = NULL;
        SDL_Rect srcRect = {88, 13, 128, 94};
        SDL_Rect destRect[3] ;
        int life = 3; // life of SpaceShip
    public:
        // ctor
        Life(SDL_Renderer*, SDL_Texture*);
        void draw();
        void operator -- (int);
        void operator ++ (int);
        bool operator < (int a);
        void dec();
        void inc();
        int get_life();
        void reset_life();

};

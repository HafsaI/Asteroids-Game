#include<SDL.h>
#include<iostream>
#include "GameObject.hpp"
#pragma once


using namespace std;

class Asteroid 
{
    protected:
    SDL_Renderer *gRenderer;
    SDL_Texture * assets;
    SDL_Rect srcRect[4];
    SDL_Rect destRect;
    int frame = 0;   
    int asteroid_angle;

    public:
        // ctor
        Asteroid(SDL_Renderer *renderer, SDL_Texture *asst, int a);
        Asteroid(SDL_Renderer *renderer, SDL_Texture *asst);
        int position_x();
        int position_y();
        void asteroidMover();
        void draw();
        SDL_Rect get_srcRect();
        SDL_Rect get_destRect();
        
};

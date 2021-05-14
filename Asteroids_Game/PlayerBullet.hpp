#include "GameObject.hpp"
#include <SDL.h>
#pragma once

class PlayerBullet: public GameObject
{
    protected:
        SDL_Renderer * gRenderer;
        SDL_Texture * assets;
        double bullet_angle = 0;
        //SDL_Rect srcRect = {120,300,150,259}; //for that other image
        SDL_Rect srcRect = {45,266,10,32};
        SDL_Rect destRect;
        bool OutOfScreen ;
        int speed = 15; 
    public:
        PlayerBullet(SDL_Renderer*, SDL_Texture*, SDL_Rect, int);
        void draw();
        void update();
        bool getOutOfScreen();
        void set_bullet_angle(double angle);
        SDL_Rect get_destRect();
};
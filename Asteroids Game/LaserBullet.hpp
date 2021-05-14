#include "GameObject.hpp"
#pragma once

class LaserBullet: public GameObject
{
    protected:
        SDL_Renderer * gRenderer;
        SDL_Texture * assets;
        double bullet_angle = 0;
        //SDL_Rect srcRect = {120,300,150,259}; //for that other image
        SDL_Rect srcRect = {454,8,16,60};
        SDL_Rect destRect;
        bool OutOfScreen;
        int speed = 15; 
        
    public:
        LaserBullet(SDL_Renderer*, SDL_Texture*, SDL_Rect, int);
        void draw();
        void update();
        bool getOutOfScreen();
        void set_bullet_angle(double angle);
        SDL_Rect get_destRect();
};
#include "GameObject.hpp"
#pragma once
using namespace std;

// this class deals with the power up that grants you laser bullets. If we collect this object on the screen,
// the space ship will be fire lasers that will increase the score more than usuaul when it hits an asteriod.
// this power up will last for 5 shots.
class LaserPowerUp : public GameObject
{
    private:
        SDL_Renderer *gRenderer;
        SDL_Texture * asset;
        SDL_Rect srcRect = {27,64,558,347}; 
        SDL_Rect destRect; // generated randomly each time
        

    public:
        // ctor 
        LaserPowerUp(SDL_Renderer*, SDL_Texture*);
        void draw();
        SDL_Rect get_destRect();
};
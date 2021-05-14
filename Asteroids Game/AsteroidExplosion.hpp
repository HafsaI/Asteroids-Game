#include<SDL.h>
#include<iostream>
#include"Asteroid.hpp"
#pragma once

// this class inherits Asteroid class
class AsteroidExplosion : public Asteroid
{
    SDL_Rect srcRect[14];

    public:
    // ctor 
    AsteroidExplosion (SDL_Renderer *renderer, SDL_Texture *asst, SDL_Rect dest) : Asteroid(renderer, asst)
    {
        destRect = dest;
        srcRect[0] = {30,19,66,76};
        srcRect[1] = {140,9,96,109};
        srcRect[2] = {263,1,108,121};
        srcRect[3] = {391,4,113,119};
        srcRect[4] = {11,133,106,115};
        srcRect[5] = {141,134,102,114};
        srcRect[6] = {269,141,95,97};
        srcRect[7] = {398,142,93,92};
        srcRect[8] = {24,273,79,88};
        srcRect[9] = {165,294,47,53};
        srcRect[10] = {292,294,48,52};
        srcRect[11] = {421,296,45,49};
        srcRect[12] = {37,424,45,49};
        srcRect[13] = {164,424,45,49};
    }
    void draw();
};
#include <SDL.h>
//#include "GameObject.hpp"
#include "PlayerBullet.hpp"
#include <string>
#include <list>

#pragma once

using namespace std;
class SpaceShip : public GameObject
{
    protected:
        SDL_Renderer * gRenderer;
        SDL_Texture * assets;
        double angle = 0;
        SDL_Rect srcRect = {88, 13, 128, 94};
        SDL_Rect destRect = {370, 270, 60, 60}; //initial pos of ship

    public:
        // ctors 
        SpaceShip(SDL_Renderer*, SDL_Texture*, SDL_Texture*);
        //SpaceShip(SDL_Renderer *renderer, SDL_Texture *asst, SDL_Rect mover);
        
        void moveShip(char move, bool pressed);
        void draw();
        void update();
        void makeMove(char move, bool pressed);
        // void InputHandle(SDL_Event e);
        SDL_Rect *get_destRect();
        int get_angle();
        

};
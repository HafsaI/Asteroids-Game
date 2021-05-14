#include "SpaceShip.hpp"
#include <iostream>
using namespace std;

SpaceShip::SpaceShip(SDL_Renderer *renderer, SDL_Texture *asst, SDL_Texture *bulletOn ) {
   gRenderer = renderer;
   assets = asst;
}

void SpaceShip::draw()
{
    SDL_RenderCopyEx(gRenderer, assets, &srcRect, &destRect, angle, NULL, SDL_FLIP_VERTICAL);
}


// void SpaceShip:: InputHandle(SDL_Event e)
// {
//     if(e.type == SDL_KEYDOWN)
//     {
//         switch (e.key.keysym.sym)
//         {
//         case SDLK_UP:
//             moveShip('u',1);
//             break;
//         case SDLK_DOWN:
//             moveShip('d',1);
//             break;
//         case SDLK_LEFT:
//             moveShip('l',1);
//             break;
//         case SDLK_RIGHT:
//             moveShip('r',1);
//             break;
//         case SDLK_SPACE:
//             moveShip('s',1);
//             break;
//         //default:
//            // break;
//         }
//     }
    // if(e.type == SDL_KEYUP)
    // {
    //     switch (e.key.keysym.sym)
    //     {
    //     case SDLK_UP:
    //         moveShip('u',0);
    //         break;
    //     case SDLK_DOWN:
    //         moveShip('d',0);
    //         break;
    //     case SDLK_LEFT:
    //         moveShip('l',0);
    //         break;
    //     case SDLK_RIGHT:
    //         moveShip('r',0);
    //         break;
    //     case SDLK_SPACE:
    //         moveShip('s',0);
    //         break;
    //    // default:
    //        // break;
    //     }
    // }
// }
void SpaceShip:: update()
{
    
}

//try use keyboard state SDL function
void SpaceShip::moveShip(char move , bool pressed)
{
    if (move == 'u')
    {
        destRect.y -= (15*cos(angle*PI/180));
        destRect.x += (15*sin(angle*PI/180));
    }
    else if (move == 'd')
    {
        destRect.y += (15*cos(angle*PI/180));
        destRect.x -= (15*sin(angle*PI/180));
    }
    else if (move == 'l')
    {
        angle-=15;
    }
    else if (move == 'r')
    {
        angle+=15;
    }
}

void SpaceShip::makeMove(char move, bool pressed)
{
   
}

SDL_Rect * SpaceShip::get_destRect()
{
    return &destRect;
}

int SpaceShip::get_angle()
{
    return angle;
}
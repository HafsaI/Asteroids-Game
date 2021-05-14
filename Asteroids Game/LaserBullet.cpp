#include "LaserBullet.hpp"
#include <iostream>
using namespace std;


LaserBullet::LaserBullet(SDL_Renderer *renderer, SDL_Texture *asst, SDL_Rect mover, int angle)
{
    
    gRenderer = renderer;
    assets = asst;
    destRect = mover;
    bullet_angle = angle;

    //adjusting laser size & position wrt spaceship
    destRect.y = mover.y+26;
    destRect.x = mover.x+26;
    
    destRect.w = 5;  //adjusts size
    destRect.h = 50;

}

void LaserBullet:: draw()
{
    SDL_RenderCopyEx(gRenderer, assets, &srcRect, &destRect, bullet_angle, NULL, SDL_FLIP_NONE); //bullet drawn acc to pos of ship
}

//gives a TRUE if bullet leaves screen(does not hit an asteroid)
bool LaserBullet:: getOutOfScreen()
{
    return OutOfScreen;
}

void LaserBullet:: update()
{
    if (destRect.y > -100) //until not out of screen fully
    { 
        destRect.y -= (15*cos(bullet_angle*PI/180));
        destRect.x += (15*sin(bullet_angle*PI/180)); //move bullet up from the pos it got fired
    }
    else
    {
        OutOfScreen = true;
    }       
}

void LaserBullet::set_bullet_angle(double angle)
{
    bullet_angle = angle;
}

SDL_Rect LaserBullet::get_destRect()
{
    return destRect;
}
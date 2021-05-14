#include "PlayerBullet.hpp"
using namespace std;

PlayerBullet::PlayerBullet(SDL_Renderer *renderer, SDL_Texture *asst, SDL_Rect mover, int angle)
{
    gRenderer = renderer;
    assets = asst;
    destRect = mover;
    bullet_angle = angle;

    //adjusting bullets size & position wrt spaceship
    destRect.y = mover.y+26;
    destRect.x = mover.x+26;

    destRect.w = 5;  //adjusts size
    destRect.h = 10;
}

void PlayerBullet:: draw()
{
    SDL_RenderCopyEx(gRenderer, assets, &srcRect, &destRect, bullet_angle, NULL, SDL_FLIP_NONE); //bullet drawn acc to pos of ship
}

//gives a TRUE if bullet leaves screen(does not hit an asteroid)
bool PlayerBullet:: getOutOfScreen()
{
    return OutOfScreen;
}


void PlayerBullet:: update()
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

void PlayerBullet::set_bullet_angle(double angle)
{
    bullet_angle = angle;
}

SDL_Rect PlayerBullet::get_destRect()
{
    return destRect;
}
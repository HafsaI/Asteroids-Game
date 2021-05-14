#include "Asteroid.hpp"

Asteroid::Asteroid(SDL_Renderer *renderer, SDL_Texture *asst)
{
    gRenderer = renderer;
    assets = asst;
    srcRect[0] = {13,7,90,83};
    srcRect[1] = {128,4,99,88};
    srcRect[2] = {266,1,84,94};  
    srcRect[3] = {379,5,98,88};
    destRect = {position_x(), position_y(), 50, 50}; 
}

Asteroid::Asteroid(SDL_Renderer *renderer, SDL_Texture *asst, int a)
{
    gRenderer = renderer;
    assets = asst;
    srcRect[0] = {13,7,90,83};
    srcRect[1] = {128,4,99,88};
    srcRect[2] = {266,1,84,94};  
    srcRect[3] = {379,5,98,88};
    destRect = {position_x(), position_y(), 50, 50}; 
    asteroid_angle = a;
}

// this function will create a random value for position x
int Asteroid::position_x()
    {
        int r;
        int choose;
        choose = rand() % 2;
        if(choose == 0){r = (rand() % 351) + 1;}
        else if(choose == 1){r = (rand() % 800) + 600;}       
        return r;
    }

// this function will create a random value for position y
int Asteroid::position_y()
{
    int r;
    int choose;
    choose = rand() % 2;
    if(choose == 0){r = (rand() % 150) + 1;}
    else if(choose == 1){r = (rand() % 600) + 550;}       
    return r;
}


void Asteroid::asteroidMover()
{ 
    if (destRect.x >= 800  && destRect.y <= 600)
    {
        //destRect.y = 600 - destRect.y ;
        destRect.x = 0;
        //destRect.y = 0;
    }
    else  if (destRect.x <= 0  && destRect.y <= 600)
    {
        //destRect.y = 600 - destRect.y ;
        destRect.x = 800;
        //destRect.y = 0;
    }
    else  if (destRect.x <= 800 && destRect.y >= 600)
    {
        destRect.y = 0;
        //destRect.x = 800 - destRect.x;
        //destRect.x = 0;
    }
      else  if (destRect.x <= 800 && destRect.y <= 0)
    {
        destRect.y = 600;
        //destRect.x = 800 - destRect.x;
        //destRect.x = 0;
    }
     else  if (destRect.x >= 800 && destRect.y >= 600)
    {
        destRect.y = 0;
        destRect.x = 0;
    }
     else  if (destRect.x <= 0 && destRect.y <= 0)
    {
        destRect.y = 600;
        destRect.x = 800;
    }
    destRect.y -= (10*cos(asteroid_angle*PI/180));
    destRect.x += (10*sin(asteroid_angle*PI/180)); 
}

// getters
SDL_Rect Asteroid::get_srcRect()
{
    return srcRect[frame];
}

SDL_Rect Asteroid::get_destRect()
{
    return destRect;
}

void Asteroid::draw()
{
    SDL_RenderCopy(gRenderer, assets, &srcRect[frame], &destRect);
    frame += 1;
    if (frame == 4){
        frame = 0;
    }
    
}
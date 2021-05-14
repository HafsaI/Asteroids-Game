#include "ExtraLife.hpp"

ExtraLife::ExtraLife(SDL_Renderer *renderer, SDL_Texture *asst)
{
    gRenderer = renderer;
    asset = asst;
    destRect = {position_x(), position_y(), 50, 50}; 
}

// this function will create a random value for position x
int ExtraLife::position_x()
{
    int r;
    int choose;
    choose = rand() % 2;
    if(choose == 0){r = (rand() % 351) + 1;}
    else if(choose == 1){r = (rand() % 800) + 600;}       
    return r;
}

// this function will create a random value for position y
int ExtraLife::position_y()
{
    int r;
    int choose;
    choose = rand() % 2;
    if(choose == 0){r = (rand() % 240) + 1;}
    else if(choose == 1){r = (rand() % 600) + 350;}       
    return r;
}

void ExtraLife::draw()
{
    SDL_RenderCopy(gRenderer, asset, &srcRect, &destRect);
}

int ExtraLife::get_NumOfExtraLives()
{
    return n;
}

SDL_Rect ExtraLife::get_destRect()
{
    return destRect;
}
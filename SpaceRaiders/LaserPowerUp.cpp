#include "LaserPowerUp.hpp"

LaserPowerUp::LaserPowerUp(SDL_Renderer *renderer, SDL_Texture *image)
{
    gRenderer = renderer;
    asset = image;
    int x = rand() % 800 + 1;
    int y = rand() % 600 + 1;
    destRect = {x,y,30,30};
}

void LaserPowerUp::draw()
{
    SDL_RenderCopy(gRenderer, asset, &srcRect, &destRect); // draw at random point
}

SDL_Rect LaserPowerUp::get_destRect()
{
    return destRect;
}
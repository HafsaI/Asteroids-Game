#include "AsteroidExplosion.hpp"

void AsteroidExplosion::draw()
{
    SDL_RenderCopy(gRenderer, assets, &srcRect[frame], &destRect);
    frame += 1;
    if (frame == 14){
        frame = 0;
    }
}
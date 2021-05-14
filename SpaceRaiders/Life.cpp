#include "Life.hpp"

Life::Life(SDL_Renderer *renderer, SDL_Texture *asst)
{
    gRenderer = renderer;
    asset = asst;
    destRect[0] = {30, 30, 30, 22};
    destRect[1] = {70, 30, 30, 22};
    destRect[2] = {110, 30, 30, 22};
}

void Life::draw()
{
    for(int i = 0; i < life; i++)
    {
        SDL_RenderCopy( gRenderer, asset, &srcRect, &destRect[i]);
    }
}

void Life::dec()
{
    life--;
}

void Life::inc()
{
    life++;
}

void Life:: operator -- (int)
{
    life--;
}

void Life:: operator ++ (int)
{
    life++;
}

bool Life:: operator < (int a)
{
    return (a > life);
}

int Life::get_life()
{
    return life;
}

void Life::reset_life()
{
    life = 3;
}
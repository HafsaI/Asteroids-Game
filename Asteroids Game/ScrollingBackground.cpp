#include "ScrollingBackground.hpp"

ScrollingBackground:: ScrollingBackground(){
    width = 800;
    height = 600;
    background = NULL;
    scrollingOffset = 0;
}

ScrollingBackground:: ~ScrollingBackground(){
    SDL_DestroyTexture(background);
    width = height = scrollingOffset = 0;
}



void ScrollingBackground:: renderBG(int x, int y, SDL_Renderer* gRenderer)
{
    SDL_Rect renderQuad = {x,y,width, height};
    SDL_RenderCopy(gRenderer, background, NULL, &renderQuad);
}

void ScrollingBackground::drawBG(SDL_Renderer* gRenderer){
    scrollingOffset -=5;
    if (scrollingOffset < -height){
        scrollingOffset = 0;
    }

    renderBG(0, scrollingOffset, gRenderer);
    renderBG(0, scrollingOffset + height, gRenderer);

}
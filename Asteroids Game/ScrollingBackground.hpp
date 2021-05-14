#include <SDL.h>
#pragma once

class ScrollingBackground{
    public:
        SDL_Texture* background;
        int width, height, scrollingOffset;
    
        ScrollingBackground();
        ~ScrollingBackground();
        void renderBG(int, int, SDL_Renderer*);
        void drawBG(SDL_Renderer*);



};  
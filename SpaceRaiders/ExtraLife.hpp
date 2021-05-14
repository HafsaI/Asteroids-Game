#include "GameObject.hpp"
#pragma once
using namespace std;


// this class deals with the power up that grants you an extra life. If we collect this object on the screen,
// our life will be increased by one. If life is already full (i.e. 3) then nothing happens.
class ExtraLife : public GameObject
{
    protected:
        SDL_Renderer *gRenderer;
        SDL_Texture * asset;
        SDL_Rect srcRect = {0,0,512,512};
        SDL_Rect destRect;
        const int n = 3; // number of extra lives than can appear in a level. 

    public:
        // ctor
        ExtraLife(SDL_Renderer*, SDL_Texture*);

        void draw();
        SDL_Rect get_destRect();
        int position_x();
        int position_y();
        int get_NumOfExtraLives();

};
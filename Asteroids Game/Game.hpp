#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "SpaceShip.hpp"
#include "Asteroid.hpp"
#include "PlayerBullet.hpp"
#include "ScrollingBackground.hpp"
#include "AsteroidExplosion.hpp"
#include "ExtraLife.hpp"
#include "Life.hpp"
#include "LaserPowerUp.hpp"
#include "LaserBullet.hpp"
#include <fstream>
using namespace std;

class Game{

    protected:
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture---(a 2d image maybe)
    SDL_Texture* gTexture = NULL;
    SDL_Texture* spaceship_tex = NULL;
    SDL_Texture* bulletOne_tex = NULL;
    SDL_Texture* menu_tex = NULL;
    SDL_Texture* asteroid_tex = NULL;
    SDL_Texture* instructions_tex = NULL;
    SDL_Texture* explosion_tex = NULL;
    SDL_Texture* extraLife_tex = NULL;
    SDL_Texture* paused_tex = NULL;
    SDL_Texture* laserPowerUp_tex = NULL;
    SDL_Texture* gGameover_tex = NULL;
    TTF_Font *ScoreFont = NULL; 
    Mix_Music *bgMusic = NULL;
    
    SpaceShip* s_ship;
    list<Asteroid*>asteroidS;
    list<PlayerBullet*> bullets;
    list<LaserBullet*> laser_bullets;
    list<AsteroidExplosion*> explodedAsteroid;
    list<ExtraLife*> extra_life;
    list<LaserPowerUp*> laser_powerUp;
    ScrollingBackground textureBG;
    Life* life;
    
    SDL_Surface* surfaceMessage = NULL;
    SDL_Surface* surfaceMessage1 = NULL;
    SDL_Surface* surfaceMessage2 = NULL;
    
    SDL_Texture* Message = NULL; 
    SDL_Texture* Message1 = NULL;
    SDL_Texture* Message2 = NULL;
    
    SDL_Colour text_color;
    SDL_Colour text_color1 = {255,255,255,255};

    string strr;
    int FinalScore = 0;
    int score = 0; 
    bool quit = false;
    bool powerUp = false;
    bool paused = false;
    int n = 0; // number of laser bullets that a power up grants you. 
    enum game_states
    {
        MENU = 0,
        INSTRUCTIONS = 1,
        PLAY = 2,
        GAMEOVER = 3
    };
    int m_currentGameState = MENU;

    enum levels
    {
        LEVEL1 = 0,
        LEVEL2 = 1,
        LEVEL3 = 2 
    };
    int currentLevel = LEVEL1;

public:
    // dtor

    // all functions 
    bool init(); 
    bool loadMedia(); 
    void close(); 
    SDL_Texture* loadTexture( std::string path );
    void run();
    void DrawAllObjects();
    void UpdateObjects();
    bool HandleEvents(SDL_Event e);
    void init_levels();
    void CollisionDetection();
    void reset();
    void draw_paused();
    bool check_HiScore();
    
    void ToggleFullscreen(SDL_Window* Window) 
    {
        Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
        bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
        SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
        SDL_ShowCursor(IsFullscreen);
    }
    
};


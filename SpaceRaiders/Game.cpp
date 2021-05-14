#include "Game.hpp"
#include <list>
#include <time.h>
using namespace std;

// Game::~Game() 
// {          
//     // for (auto f: asteroidS) {
// 	//    delete f;
// 	//    f = NULL; 
//     // }
// 	// asteroidS.clear(); 

//     // for (auto f: bullets) {
// 	//    delete f; 
// 	//    f = NULL; 
//     // }
//     // bullets.clear(); 

//     // for (auto p:laser_bullets) {
// 	//    delete p; 
// 	//    p = NULL; 
//     // }
//     // laser_bullets.clear(); 
	
// 	// for (auto p:explodedAsteroid) {
// 	//    delete p; 
// 	//    p = NULL; 
//     // }
//     // explodedAsteroid.clear(); 

// 	// for (auto p:extra_life) {
// 	//    delete p; 
// 	//    p = NULL; 
//     // }
//     // extra_life.clear(); 

// 	// for (auto p:laser_powerUp) {
// 	//    delete p; 
// 	//    p = NULL; 
//     // }
//     // laser_powerUp.clear(); 

// 	// delete s_ship;
// 	// delete life;	
// }

bool Game::init()
{
	
	bool success = true;
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{


		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Space Raiders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else 
		{
			
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
			
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				//Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
			}
		}
	}
	ofstream GameFile("SpaceRaidersHighScore.txt");
	GameFile << "00";
	GameFile.close();
	return success;
}


bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
    gTexture = loadTexture("space.png");
	bgMusic = Mix_LoadMUS( "space.wav" );
	spaceship_tex = loadTexture("spaceship.png");
	bulletOne_tex = loadTexture("bulletOne.png");
	menu_tex = loadTexture("MenuScreen.png");
	asteroid_tex = loadTexture("asteroids.png");
	instructions_tex = loadTexture("instructions.png");
	explosion_tex = loadTexture("asteroidExplosion.png");
	extraLife_tex = loadTexture("extraLife.png");
	paused_tex = loadTexture("pause_resume_button.png");
	laserPowerUp_tex = loadTexture("LaserPowerup.png");
	gGameover_tex = loadTexture("GameOver.png");
	ScoreFont = TTF_OpenFont("OpenSans-Bold.ttf", 30);


	if (gTexture==NULL ||bgMusic == NULL || spaceship_tex == NULL || bulletOne_tex == NULL || menu_tex == NULL || asteroid_tex== NULL || instructions_tex == NULL) 
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

	return success;
}


void Game::close()
{
	gTexture=NULL;
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(spaceship_tex);
	SDL_DestroyTexture(bulletOne_tex);
	SDL_DestroyTexture(menu_tex);
	SDL_DestroyTexture(asteroid_tex);
	SDL_DestroyTexture(instructions_tex);
	SDL_DestroyTexture(explosion_tex);
	SDL_DestroyTexture(extraLife_tex);
	SDL_DestroyTexture(laserPowerUp_tex);
	SDL_DestroyTexture(gGameover_tex);
	SDL_DestroyTexture(paused_tex);
	

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	SDL_FreeSurface(surfaceMessage1);
	SDL_DestroyTexture(Message1);

	SDL_FreeSurface(surfaceMessage2);
	SDL_DestroyTexture(Message2);
	

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//free music
	Mix_FreeMusic( bgMusic );
    bgMusic = NULL;

	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


SDL_Texture* Game::loadTexture( std::string path ) 
//basically converting image to surface to texture
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}


//draws according to gamestate ongoing
void Game:: DrawAllObjects()
{
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(gRenderer);
   
   
	switch(m_currentGameState)
	{
		case MENU:
			SDL_RenderCopy(gRenderer, menu_tex, NULL, NULL); //draws menu image
			break;

		case INSTRUCTIONS:
			SDL_RenderCopy(gRenderer, instructions_tex, NULL, NULL); 
			break;

		case PLAY:
			textureBG.drawBG(gRenderer); 	// draws scrolling background
			s_ship -> draw(); 				// draws space ship
			life->draw();					// draws status 

			for (list<PlayerBullet*>::const_iterator iter = this->bullets.begin(),end = this->bullets.end();iter != end;++iter)
			{ 
				(*iter)->draw();			// draws bullets
			}

			for (list<Asteroid*>::const_iterator iter = this->asteroidS.begin(),end = this->asteroidS.end();iter != end;++iter)
			{		
				(*iter)->draw(); 			// draws asteriods
			}

			for (list<AsteroidExplosion*>::const_iterator iter = this->explodedAsteroid.begin(),end = this->explodedAsteroid.end();iter != end;++iter)
			{ 
				(*iter)->draw();			// draws exploded asteroids
				explodedAsteroid.erase(iter++); 
			}

			for (list<ExtraLife*>::const_iterator iter = this->extra_life.begin(),end = this->extra_life.end();iter != end;++iter)
			{ 
				(*iter)->draw();			// draws extra life power up
			}

			for (list<LaserPowerUp*>::const_iterator iter = this->laser_powerUp.begin(),end = this->laser_powerUp.end();iter != end;++iter)
			{ 
				(*iter)->draw();			// draws extra life power up
			}

			for (list<LaserBullet*>::const_iterator iter = this->laser_bullets.begin(),end = this->laser_bullets.end();iter != end;++iter)
			{ 
				(*iter)->draw();			// draws bullets
			}

			score ++;
			strr = "Score: " + to_string(score);
			surfaceMessage1 = TTF_RenderText_Solid(ScoreFont, strr.c_str(), text_color1);
			if (surfaceMessage1 != NULL)
			{
				Message1 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage1);
				SDL_Rect Message_rect1; 
				Message_rect1 = {650, 40, 120, 30}; 
				SDL_RenderCopy(gRenderer, Message1, NULL, &Message_rect1); 
			}

			if (currentLevel == LEVEL1)
			{
				string str = "Level 1";
				surfaceMessage2 = TTF_RenderText_Solid(ScoreFont, str.c_str(), text_color1);
				if (surfaceMessage2 != NULL)
				{
					Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					SDL_Rect rect; 
					rect = {650, 0, 120, 30}; 
					SDL_RenderCopy(gRenderer, Message2, NULL, &rect); 
				}
			}
			if (currentLevel == LEVEL2)
			{
				string str = "Level 2";
				surfaceMessage2 = TTF_RenderText_Solid(ScoreFont, str.c_str(), text_color1);
				if (surfaceMessage2 != NULL)
				{
					Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					SDL_Rect rect; 
					rect = {650, 0, 120, 30}; 
					SDL_RenderCopy(gRenderer, Message2, NULL, &rect); 
				}
			}
			if (currentLevel == LEVEL3)
			{
				string str = "Level 3";
				surfaceMessage2 = TTF_RenderText_Solid(ScoreFont, str.c_str(), text_color1);
				if (surfaceMessage2 != NULL)
				{
					Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					SDL_Rect rect; 
					rect = {650, 0, 120, 30}; 
					SDL_RenderCopy(gRenderer, Message2, NULL, &rect); 
				}
			}
			break;
			

		case GAMEOVER:

			SDL_RenderCopy(gRenderer, gGameover_tex, NULL, NULL); 
			string str1 = to_string(FinalScore); 
			string line;
			string str2;
			ifstream GameFile("SpaceRaidersHighScore.txt");
			while (getline (GameFile, line)) 
			{
				str2 = line;
			}
			surfaceMessage = TTF_RenderText_Solid(ScoreFont, str1.c_str(), text_color);
			if (surfaceMessage != NULL)
			{
				Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
				SDL_Rect Message_rect; 
				Message_rect = {635, 427, 50, 50}; 
				SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect); 
			}
			surfaceMessage = TTF_RenderText_Solid(ScoreFont, str2.c_str(), text_color);
			if (surfaceMessage != NULL)
			{
				Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
				SDL_Rect Message_rect; 
				Message_rect = {635, 467, 50, 50}; 
				SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect); 
			}
			break;
	}
    SDL_RenderPresent(gRenderer);
}


// draws pause button when game is paused. 
void Game::draw_paused()
{
	SDL_Rect src = {0,0,352,352};
	SDL_Rect dest = {300,200,200,200};
	SDL_RenderCopy(gRenderer, paused_tex, &src, &dest);
	SDL_RenderPresent(gRenderer); 
}

//updates objects according to gamestate(ie MENU/PLAY etc) ongoing
void Game:: UpdateObjects()
{
	list<Asteroid*>::iterator it;
	switch(m_currentGameState)
	{
		case MENU:
			break;

		case PLAY:

			CollisionDetection();
			
			//updating bullets' pos 
			for (list<PlayerBullet*>::const_iterator iter = this->bullets.begin(),end = this->bullets.end();iter != end;++iter)
			{
				(*iter)->update();
			}

			for (list<LaserBullet*>::const_iterator iter = this->laser_bullets.begin(),end = this->laser_bullets.end();iter != end;++iter)
			{
				(*iter)->update();
			}

			for (it = asteroidS.begin(); it != asteroidS.end(); it++)
			{
				(*it)->asteroidMover();
			}

			if (life->get_life() <= 0)
			{
				FinalScore = score;
				m_currentGameState = GAMEOVER;
				cout << "GAME OVER. You lost!\n";
			}

			if (asteroidS.size() == 0)
			{
				if (currentLevel < LEVEL3) 
				{
					FinalScore = score;
					currentLevel++;
					cout << "Congratulations! You destroyed all the asteroids in this level. You move onto the next level.\n";
					init_levels();
					SDL_Delay(200);
				}
				else
				{
					FinalScore = score;
					cout << "Congratulations! You cleared all the levels. You won!.\n";
					quit = true;
					if (check_HiScore())
					{
						cout << "here\n";
						string s = to_string(FinalScore);
						ofstream GameFile("SpaceRaidersHighScore.txt");
						GameFile << s;
						GameFile.close();
					}

				}
			}
			break;
	}
}


// if high score saved in file is less than final score, remove the stored score. 
bool Game::check_HiScore()
{
	bool flag = false;
	string line;
	string s = to_string(FinalScore);
	ifstream GameFile("SpaceRaidersHighScore.txt");
	while (getline (GameFile, line)) 
	{
		if (stoi(line) < FinalScore)
		{
			line.replace(line.find(s),s.length(),"");
			flag =  true; // yes the score was removed 
		}
	}
	GameFile.close();
	return flag;

}


//takes input according to gamestate ongoing
bool Game:: HandleEvents(SDL_Event e)
{
	while( SDL_PollEvent( &e ) != 0 )
	{
		// const Uint8 *keystates = SDL_GetKeyboardState( NULL );
		switch(m_currentGameState)
		{
			case MENU:
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					if (((xMouse >= 300 && xMouse <= 380) &&  ( yMouse>=44 && yMouse <=84) ) ||  ((xMouse >= 374 && xMouse <= 474) &&  ( yMouse>= 61 && yMouse <=109)) )
					{
						m_currentGameState = PLAY ; //NewGame clicked
					}
					else if( (xMouse >= 246 && xMouse <= 456) && ( yMouse>=179 && yMouse <= 213) ){ 
						m_currentGameState = INSTRUCTIONS; 
					}

					else if( (xMouse >= 382 && xMouse <= 462) && ( yMouse>=298 && yMouse <= 348) )
					{ 
						quit = true; //game closed
					}

				}
				break;
			case INSTRUCTIONS:
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					if( (xMouse >= 0 && xMouse <= 32) && ( yMouse>=0 && yMouse <= 34 ))
					{ 
						m_currentGameState = MENU; 
					}
				}
				break;

			case PLAY:
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				if(e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
						case SDLK_UP:
							s_ship->moveShip('u',1);
							break;

						case SDLK_DOWN:
							s_ship->moveShip('d',1);
							break;

						case SDLK_LEFT:
							s_ship->moveShip('l',1);
							break;

						case SDLK_RIGHT:
							s_ship->moveShip('r',1);
							break;
							
						case SDLK_SPACE:	// if spacebar is pressed, add a new bullet to the list
							if (powerUp && n < (3 - laser_powerUp.size())*5) 	// if laser bullets less than the allowed amount
																			// that is, 5 laser bullets per power up.
							{
								cout << laser_powerUp.size() << endl;
								LaserBullet * lb = new LaserBullet(gRenderer, bulletOne_tex, *s_ship->get_destRect(), s_ship->get_angle());
								laser_bullets.push_back(lb);
								n++;
							}
							else
							{
								PlayerBullet* b = new PlayerBullet(gRenderer, bulletOne_tex, *s_ship->get_destRect(), s_ship->get_angle());
								bullets.push_back(b);	
							}
							break;

						case SDLK_f:
							ToggleFullscreen(gWindow);
							break;
						
						case SDLK_ESCAPE:
							if (paused == false)
							{
								paused = true;
							}
							else
							{
								paused = false;
							}			
					}
				}

				if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					if( (xMouse >= 300 && xMouse <= 500) && ( yMouse>=200 && yMouse <= 400 ))
					{ 
						paused = false;
					}
				}
				break;

			case GAMEOVER:
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					if ((xMouse >= 85 && xMouse <= 190) &&  ( yMouse>= 446 && yMouse <= 558) ) 
					{
						reset();
						m_currentGameState = PLAY; //reset clicked on GameOver Screen
					}
					else if( (xMouse >= 220 && xMouse <= 300) && ( yMouse>= 440 && yMouse <= 560) )
					{ 
						quit = true; //Quit clicked on GameOver Screen
					}

				}
				break;
		}
	}
	return false;
}


//after gameover when person clicks retry
void Game:: reset()
{
	
	score = 0;
	bullets.clear();
	asteroidS.clear();
	explodedAsteroid.clear();
	extra_life.clear();
	laser_powerUp.clear();
	laser_bullets.clear();
	life->reset_life();

	init_levels();
}


void Game::init_levels()
{
	switch (currentLevel)
	{
		case LEVEL1:
			// create 10 random asteriods
			for (int i=0; i<10; i++)
			{
				Asteroid* s = new Asteroid(gRenderer, asteroid_tex, rand()% 360);
				asteroidS.push_back(s);	 
			}

			// A maximum of 3 extra lives can appear on the screen. 
			// A maximum of 3 laser power ups can appear on the screen.
			for (int i=0; i<3; i++)
			{
				ExtraLife * e = new ExtraLife(gRenderer, extraLife_tex);
				extra_life.push_back(e);
				LaserPowerUp * l = new LaserPowerUp(gRenderer, laserPowerUp_tex);
				laser_powerUp.push_back(l);
			}
			break;
		
		case LEVEL2:
			// create 20 random asteriods
			for (int i=0; i<20; i++)
			{
				Asteroid* s = new Asteroid(gRenderer, asteroid_tex, rand()% 360);
				asteroidS.push_back(s);	 
			}

			// A maximum of 3 extra lives can appear on the screen. 
			// A maximum of 3 laser power ups can appear on the screen.
			for (int i=0; i<3; i++)
			{
				ExtraLife * e = new ExtraLife(gRenderer, extraLife_tex);
				extra_life.push_back(e);
				LaserPowerUp * l = new LaserPowerUp(gRenderer, laserPowerUp_tex);
				laser_powerUp.push_back(l);
			}
			break;
		
		case LEVEL3:
			// create 30 random asteriods
			for (int i=0; i<30; i++)
			{
				Asteroid* s = new Asteroid(gRenderer, asteroid_tex, rand()% 360);
				asteroidS.push_back(s);	 
			}

			// A maximum of 3 extra lives can appear on the screen. 
			// A maximum of 3 laser power ups can appear on the screen.
			for (int i=0; i<3; i++)
			{
				ExtraLife * e = new ExtraLife(gRenderer, extraLife_tex);
				extra_life.push_back(e);
				LaserPowerUp * l = new LaserPowerUp(gRenderer, laserPowerUp_tex);
				laser_powerUp.push_back(l);
			}
			break;
	}
}


void Game::run()
{
	s_ship = new SpaceShip(gRenderer, spaceship_tex, bulletOne_tex);
	// asteroidS = new Asteroid(gRenderer, asteroid_tex);
	life = new Life(gRenderer, spaceship_tex);
	textureBG.background = gTexture;
	init_levels();

    SDL_RenderClear( gRenderer ); //Clear the entire screen to our selected design/colour on grenderer

	SDL_Event e;
	while( !quit )
	{
		HandleEvents(e);

		if (!paused)
		{
			UpdateObjects();
			DrawAllObjects();
		}
		else
		{
			cout << "here\n";
			draw_paused();
		}
		
		
		//for music
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_PlayMusic( bgMusic, 2 );
		}
		
		SDL_Delay(50);	//causes sdl engine to delay for specified miliseconds//delay for seconds so the window doesn't just disappear.

	}

}


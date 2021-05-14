#include "Game.hpp"

// checks for collison between objects
void Game::CollisionDetection()
{
	const SDL_Rect S = *s_ship->get_destRect(); // get current position of ship

	for (list<Asteroid*>::const_iterator i = this->asteroidS.begin(),end = this->asteroidS.end();i != end;++i)
	{
		const SDL_Rect A = (*i)->get_destRect(); // get current position of asteroid

		// check for collision b/w asteroid & bullet

		for (list<PlayerBullet*>::const_iterator j = this->bullets.begin(),end = this->bullets.end(); j != end;++j) 
		{
			const SDL_Rect B =  (*j) -> get_destRect(); // get current position of bullet
			if (SDL_HasIntersection(&A,&B))
			{ 
				bullets.erase(j++);  		// the bullet vanishes
				asteroidS.erase(i++); 	    // the asteroid vanishes
				AsteroidExplosion * a = new AsteroidExplosion(gRenderer, explosion_tex, A);
				explodedAsteroid.push_back(a);
				score += 100;
			}
		}

        // check for collision b/w asteroid & laser bullet

		for (list<LaserBullet*>::const_iterator m = this->laser_bullets.begin(),end = this->laser_bullets.end(); m != end; ++m) 
		{
			const SDL_Rect LB =  (*m) -> get_destRect(); // get current position of laser bullet
			if (SDL_HasIntersection(&A,&LB))
			{ 
				laser_bullets.erase(m++);  		// the bullet vanishes
				asteroidS.erase(i++); 	    	// the asteroid vanishes
				AsteroidExplosion * a = new AsteroidExplosion(gRenderer, explosion_tex, A);
				explodedAsteroid.push_back(a);
				score += 500;
			}
		}

		// check for collision b/w asteroid and ship

		if (SDL_HasIntersection(&A,&S))
		{
			asteroidS.erase(i++); 	    		// the asteroid vanishes
			life->dec();		                // life decreases by 1
		}
	}

    
    // check for collision between ship and extra life
    for (list<ExtraLife*>::const_iterator k = this->extra_life.begin(),end = this->extra_life.end();k != end;++k)
    { 
        const SDL_Rect E =  (*k) -> get_destRect(); // get current position of extra life
        if (SDL_HasIntersection(&E,&S))
		{
			extra_life.erase(k++); 	    // the extralife vanishes
            if (*life < 3)              // less than 3. then increase life. otherwise dont.
            {
                life->inc();             	// life increase by 1
            }              
		}
    }		

    // check for collision between ship and laser power up
    for (list<LaserPowerUp*>::const_iterator l = this->laser_powerUp.begin(),end = this->laser_powerUp.end();l != end;++l)
    { 
        const SDL_Rect L =  (*l) -> get_destRect(); // get current position of laser power up
        if (SDL_HasIntersection(&L,&S))
		{
			laser_powerUp.erase(l++); 	    // the power up vanishes
            powerUp = true;
		}
    }		
}
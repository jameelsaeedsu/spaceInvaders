#include "Session.h"
#include "System.h"
#include "Component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#define FPS 60

namespace SPACEINVASION
{

    void Session::setBackground(std::string path)
    {
        SDL_Surface* bgSurface = IMG_Load(path.c_str());
        bgTexture = SDL_CreateTextureFromSurface(system.get_renderer(), bgSurface);
        SDL_FreeSurface(bgSurface);
    }

    void Session::setIcon(std::string path)
    {
        SDL_Surface* iconSurface = IMG_Load(path.c_str());
        SDL_SetWindowIcon(system.get_window(), iconSurface);
        SDL_FreeSurface(iconSurface);
    }

    void Session::add(Component* component)
    {
        added.push_back(component);
    }

    void Session::remove(Component* component)
    {
        removed.push_back(component);
    }

    void Session::run()
    {
        Uint32 tickInterval = 1000 / FPS;
        while (!quit)
        { 
             if (gameCounter % 200 == 0)
            {               
                Enemy* enemy = Enemy::getInstance(); 
                add(enemy);
                gameCounter = 0; 
            } 
            Uint32 nextTick = SDL_GetTicks() + tickInterval;
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type) 
                {
                    case SDL_QUIT: quit = true; break;
                    case SDL_KEYDOWN:
                       for (Component* c : comps)
                           c->keyDown(event);
                       break;
                }
            }

            for (Component* c : added) 
            {
                comps.push_back(c);
            }
            added.clear(); 
           
            for (int i = 0; i < comps.size(); i++) //A, B 
            {
                for (int j = i + 1; j < comps.size(); j++)
                {
                    if (detectCollision(comps[i], comps[j]))
                    {
                        if(Player *p = dynamic_cast<Player *>(comps[i]))
                        {
                            for(Component* c : comps)
                                c->collisionDetected();
                        }
                        remove(comps[i]); //Tar bort både skottet och enemy, och player. 
                        remove(comps[j]); 
                        std::cout << comps[i]->getName() << " has collided with " << comps[j]->getName() << std::endl;
                    }
                }
            }
 
          //Itererar över komponenter i removed. Om någon komponent == komponent i comps så tas den bort.
          //Dck ingen dynamisk minnesallokering.  
            for (Component* comp : removed) 
            {
				for (std::vector<Component*>::iterator iter = comps.begin(); iter != comps.end();) {
					if (*iter == comp) 
                    {
						iter = comps.erase(iter); //Tas bara bort från listen. Vet ej om dessa tas bort dynamiskt??? 
                    }
					else
						iter++;
				}
            }

            for (std::vector<Component*>::iterator iter = removed.begin(); iter != removed.end();) 
            {
				delete *iter; 
                iter++; 
			}
            removed.clear();  

            for (Component* c : comps) 
            {
                if (c->tick() == 1)
                {
                    removed.push_back(c);
                    
                    if(Enemy* e = dynamic_cast<Enemy *>(c))
                    {
                        std::cout << "\nEnemy has passed the player zone\n" << std::endl;
                        quit = true;
                    }
                }
            }
            
            SDL_RenderClear(system.get_renderer());
            SDL_RenderCopy(system.get_renderer(), bgTexture, NULL, NULL);

            for (Component* c : comps)
                c->draw();

            SDL_RenderPresent(system.get_renderer());

            int delay = nextTick - SDL_GetTicks();
		    if (delay > 0)
			    SDL_Delay(delay);
            
            gameCounter++; 
        }
    }

    bool Session::detectCollision(Component* a, Component* b)
    {
        if(a->getRect().x < b->getRect().x + b->getRect().w 
        && a->getRect().x + a->getRect().w > b->getRect().x 
        && a->getRect().y < b->getRect().y + b->getRect().h 
        && a->getRect().y + a->getRect().h > b->getRect().y)
        {
            return true;
        }
        return false;
    }

    Session::~Session()
    {
        removed.clear();
        added.clear();
        for (std::vector<Component*>::iterator iter = comps.begin(); iter != comps.end();) 
        {
			delete *iter; 
            iter++; 
	    }
    }

}
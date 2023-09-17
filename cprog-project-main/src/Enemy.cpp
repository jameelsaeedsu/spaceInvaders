#include "Enemy.h"
#include "Component.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL_mixer.h>

namespace SPACEINVASION

{
    Enemy::Enemy() : Component(0, 0, 50, 50)
    {
        int randomXpos = rand() % system.getWindowWidth(); 
        rect.x = (randomXpos-rect.w/2);
        rect.y = system.getWindowHeight()/20-(rect.h)-10;
	    SDL_Surface* enemySurface = IMG_Load("../../resources/images/enemy.png");
	    enemyTexture = SDL_CreateTextureFromSurface(system.get_renderer(), enemySurface);
        SDL_SetTextureColorMod(enemyTexture, 200, 0, 0);
	    SDL_FreeSurface(enemySurface);
        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        enemyMusic = Mix_LoadWAV("../../resources/sounds/gameOver.wav");
    }

    Enemy* Enemy::getInstance()
    {
        return new Enemy(); 
    }

    void Enemy::draw() const
    {
        const SDL_Rect &rect = getRect();
        SDL_RenderCopy(system.get_renderer(), enemyTexture, NULL, &rect);
    }

     int Enemy::tick()
    {
        if (getRect().y >= system.getWindowHeight() - getRect().h)
        {
            Mix_PlayChannel(-1, enemyMusic, 0);
            Mix_Volume(-1, 100);
            SDL_Delay(3000);
            return 1;
        }
        rect.y++; 
        return 0; 
    }

    std::string Enemy::getName()
    {
        return "Enemy";
    }

    Enemy::~Enemy()
    {
        SDL_DestroyTexture(enemyTexture);
        std::cout << "Enemy: Destructor " << std::endl; 
        Mix_FreeChunk(enemyMusic);
        Mix_CloseAudio();
    }

}
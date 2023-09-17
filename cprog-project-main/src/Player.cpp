#include "Player.h"
#include "Component.h"
#include "System.h"
#include "Session.h"
#include "Bullet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <SDL2/SDL_mixer.h>


namespace SPACEINVASION

{
    Player::Player(Session& session): Component(0, 0, 50, 50)
    {
        pointerSession = &session;
        rect.x = (system.getWindowWidth()/2-rect.w/2);
        rect.y = (system.getWindowHeight()-(rect.h*1.5));
        SDL_Surface* playerSurface = IMG_Load("../../resources/images/player.png");
        playerTexture = SDL_CreateTextureFromSurface(system.get_renderer(), playerSurface);
        SDL_FreeSurface(playerSurface);
        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        gameOverAudio = Mix_LoadWAV("../../resources/sounds/gameOver.wav");
        playerShootAudio = Mix_LoadWAV("../../resources/sounds/shotFired.wav");
    }

    Player* Player::getInstance(Session& session)
    {
        return new Player(session); 
    }

    void Player::shoot()
    {
        Mix_PlayChannel(-1, playerShootAudio, 0);
        Mix_Volume(-1, 20);
        pointerSession->add(Bullet::getInstance((getRect().x + getRect().w / 2), getRect().y));
    }

    void Player::draw() const
    {
        const SDL_Rect &rect = getRect();
        SDL_RenderCopy(system.get_renderer(), playerTexture, NULL, &rect);
    }

    void Player::keyDown(const SDL_Event& event) 
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        case SDLK_SPACE:
            if (event.key.repeat == 0)
                shoot();
            break;
        case SDLK_LEFT:
            if(getRect().x > 0)
                rect.x = rect.x - 30; 
            break;
        case SDLK_RIGHT:
            if(getRect().x < 650)
                rect.x = rect.x + 30;
            break;
        }
    }

    void Player::collisionDetected()
    {
        Mix_PlayChannel(-1, gameOverAudio, 0);
        Mix_Volume(-1, 100);
        SDL_Delay(3000);
        pointerSession->quit = true;
    }

        int Player::tick()
    {
        return 0; 
    }

    std::string Player::getName()
    {
        return "Player";
    }

    Player::~Player()
    {
        SDL_DestroyTexture(playerTexture);
        Mix_FreeChunk(gameOverAudio);
        Mix_FreeChunk(playerShootAudio);
        Mix_CloseAudio();
    }
}

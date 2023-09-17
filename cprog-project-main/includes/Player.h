#pragma once
#include "Component.h"
#include <SDL2/SDL.h>
#include "Bullet.h"
#include "Session.h"
#include <string>
#include <SDL2/SDL_mixer.h>

namespace SPACEINVASION

{
    class Player : public Component
    {
    public:
        static Player* getInstance(Session&);
        ~Player();
    protected: 
        Player(Session&);  
        void shoot();
        void keyDown(const SDL_Event&);
        void collisionDetected();
        void draw() const;
        int tick();
        std::string getName();
    private:
        Session *pointerSession;
        SDL_Texture *playerTexture;
        Mix_Chunk* gameOverAudio;
        Mix_Chunk* playerShootAudio;
    };
}
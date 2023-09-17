#pragma once
#include "Component.h"
#include <SDL2/SDL.h>
#include <string> 
#include <SDL2/SDL_mixer.h>

namespace SPACEINVASION

{
    class Enemy: public Component 
    {
    public:
        static Enemy* getInstance(); 
        ~Enemy(); 
    protected:
        int tick();
        void draw() const;
        std::string getName();
    private:
        Enemy();
        SDL_Texture* enemyTexture;
        Mix_Chunk* enemyMusic;
    };
}
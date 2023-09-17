#pragma once
#include "Component.h"
#include <string>
namespace SPACEINVASION

{
    class Bullet : public Component
    {
    public:
        static Bullet* getInstance(int x, int y);
        ~Bullet();
    protected:
        Bullet(int x, int y);
        int tick();
        void draw() const;
        std::string getName();
    private:
        SDL_Texture *bulletTexture;
    };
}

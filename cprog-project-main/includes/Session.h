#pragma once
#include "Component.h"
#include <vector>
#include <string>

namespace SPACEINVASION

{
    class Session
    {
    public:
        void setIcon(std::string path);
        void setBackground(std::string path);
        void add(Component*);
        void run();
        ~Session();
        bool quit = false;
    private:
        int gameCounter = 0; 
        SDL_Texture* bgTexture;
        std::vector<Component*> comps;
	    std::vector<Component*> added, removed;
        void remove(Component*);
        bool detectCollision(Component*, Component*);
    };

}



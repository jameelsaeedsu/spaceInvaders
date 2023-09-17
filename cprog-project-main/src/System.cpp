#include <SDL2/SDL.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include <string>

namespace SPACEINVASION

{
    System::System(std::string name, int setWidth, int setHeight)
    {
        width = setWidth;
        height = setHeight;
        SDL_Init(SDL_INIT_EVERYTHING);
	    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, setWidth, setHeight, 0);
	    renderer = SDL_CreateRenderer(window, -1, 0);
    }

    const int System::getWindowWidth() const
    {
        return width;
    }

    const int System::getWindowHeight() const
    {
        return height;
    }

    SDL_Renderer* System::get_renderer() const
    {
        return renderer;
    }

    SDL_Window* System::get_window() const
    {
        return window;
    }

    System::~System() 
    {   
	    SDL_DestroyWindow(window);
	    SDL_DestroyRenderer(renderer);
	    SDL_Quit();
    }

    System system("Space Invaders", 700, 500);

}
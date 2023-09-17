#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace SPACEINVASION
{
    class System
    {
    public:
        System(std::string, int, int);
		~System();
        SDL_Renderer* get_renderer() const;
        SDL_Window* get_window() const;
        const int getWindowWidth() const;
        const int getWindowHeight() const;
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int width;
        int height;
    };
    extern System system;
}
#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace SPACEINVASION

{
	class Component
	{
	public:
		virtual std::string getName() = 0;
		virtual void keyDown(const SDL_Event&) {}
		virtual void draw() const = 0;
		const SDL_Rect& getRect() const { return rect; }
		virtual int tick() = 0;
		virtual void collisionDetected() {}
		virtual ~Component() = default; 
	protected:
		SDL_Rect rect;
		Component(int x, int y, int w, int h) : rect{x, y, w, h} {}
	private:
		Component(const Component&) = delete;
		const Component& operator=(const Component&) = delete;
	};
}

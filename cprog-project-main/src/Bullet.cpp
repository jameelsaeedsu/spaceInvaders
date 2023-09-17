#include "Component.h"
#include "Bullet.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

 namespace SPACEINVASION

{
	Bullet::Bullet(int x, int y): Component(x - 5, y - 25, 10, 20)
	{
		SDL_Surface* bulletSurface = IMG_Load("../../resources/images/bullet.png");
	    bulletTexture = SDL_CreateTextureFromSurface(system.get_renderer(), bulletSurface);
	    SDL_FreeSurface(bulletSurface);
	}

	Bullet* Bullet::getInstance(int x, int y) 
	{
		return new Bullet(x, y);
	}

	void Bullet::draw() const 
	{
		const SDL_Rect &rect = getRect();
        SDL_RenderCopy(system.get_renderer(), bulletTexture, NULL, &rect);
	}

	int Bullet::tick() 
	{
		if (getRect().y <= 0)
			return 1; 
		rect.y = rect.y - 10;
		return 0; 
	}

	std::string Bullet::getName()
	{
		return "Bullet";
	}

	Bullet::~Bullet() 
	{
		SDL_DestroyTexture(bulletTexture);
		std::cout << "Bullet: Destructor" << std::endl; 
	}
}
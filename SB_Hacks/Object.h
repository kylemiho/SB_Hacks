#pragma once
#include "vector2.h"
#include "Globals.h"
#include <vector>
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "sprite.h"

class Object
{
	protected:
		Vector2 position;
		Vector2 scale;

		SDL_Surface *surface;

		std::vector<SDL_Texture*> textures;
		std::vector<SDL_Rect> clippingArea;

		void draw();
		virtual void renderObject(SDL_Rect renderLocation); //to be overriden by unit clas

	public:
		Object(const Vector2 &position, const Vector2& scale, const std::string filename, Sprite *sprite);
		Object();
		~Object();

		void run();
		void moveX(const double &amount); //move object's x coordinate by amount
		void moveY(const double &amount); //move object's y coordinate by amount

};
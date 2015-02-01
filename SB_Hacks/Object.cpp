#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	position = Vector2(0, 0); //when unit class calls object default constructor, we need to set position to 0 as we ignore it in unit class
}

Object::Object(const Vector2 &position, const Vector2& scale, const std::string filename, Sprite *sprite)
	:
	position(position),
	scale(scale)
{
	//default initializations
	SDL_Rect tempClippingArea;

	

	//clipping part of sprite sheet
	if (sprite)
	{
		tempClippingArea.x = sprite->x;
		tempClippingArea.y = sprite->y;
		tempClippingArea.w = sprite->w;
		tempClippingArea.h = sprite->h;
	}
	else //clip entire sheet
	{
		tempClippingArea.x = 0;
		tempClippingArea.y = 0;
		tempClippingArea.w = 0;
		tempClippingArea.h = 0;
	}
	//pushes back the default animation clipping area into our vector of clipping areas
	clippingArea.push_back(tempClippingArea);

	SDL_Surface *s = IMG_Load(filename.c_str());

	if (!s)
	{
		std::cout << "Failed to load object @: " << filename << "\n";
	}
	SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(globals::renderer, s);
	
	//add texture to list of textures for the object (an object can have animations from multiple files)
	textures.push_back(tempTexture); 
	SDL_FreeSurface(s);


}

Object::~Object()
{

}

void Object::draw()
{
	renderObject(clippingArea.at(0));
}

void Object::moveX(const double &amount)
{
	position.x += amount;
}

void Object::moveY(const double &amount)
{
	position.y += amount;
}

void Object::run()
{
	draw();
}

void Object::renderObject(SDL_Rect renderLocation)
{
	SDL_Rect ImageDimensions;
	ImageDimensions.x = position.x;
	ImageDimensions.y = position.y;
	ImageDimensions.w = scale.x;
	ImageDimensions.h = scale.y;
	if ((renderLocation.w == 0) && (renderLocation.h == 0)) //render entire sprite sheet
	{
		SDL_RenderCopy(globals::renderer, textures.at(0), NULL, &ImageDimensions);
	}
	else   
	{
		SDL_RenderCopy(globals::renderer, textures.at(0), &renderLocation, &ImageDimensions);
	}

}

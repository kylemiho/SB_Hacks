#include "stdafx.h"
#include "Unit.h"

//variables that unit uses for object positions as well
int tileSize = 40;
int boardOffset = 30;

Unit::Unit(const Vector2 &boardPosition, const Vector2& scale2, const std::string filename, Sprite *sprite, const int &maxMovement)
:
maxMovement(maxMovement),
boardPosition(boardPosition)
{
	//default initializations
	SDL_Rect tempClippingArea;
	scale.x = scale2.x;
	scale.y = scale2.y;

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

Unit::~Unit()
{

}

int Unit::getMaxMovement() const
{
	return maxMovement;
}

Vector2 Unit::getLocation() const
{
	return boardPosition;
}

void Unit::addLocation(Vector2 &amount)
{
	boardPosition.x += amount.x;
	boardPosition.y += amount.y;
}

void Unit::renderObject(SDL_Rect renderLocation)
{
	SDL_Rect ImageDimensions;
	ImageDimensions.x = (boardPosition.x*tileSize)+boardOffset;
	ImageDimensions.y = (boardPosition.y*tileSize)+boardOffset;
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
#pragma once

#include "Globals.h"
#include "Object.h"
#include "sprite.h"
#include "vector2.h"

#include <SDL.h>
#include <SDL_image.h>

class Object;
class Sprite;
class Vector2;

class Unit : public Object
{
public:
	Unit(const Vector2 &boardPosition, const Vector2& scale, const std::string filename, Sprite *sprite, const int &maxMovement);
	~Unit();

	int getMaxMovement() const;
	Vector2 getLocation() const;
	void addLocation(Vector2 &amount);

protected:
	//additional member variables for unit class
	Vector2 boardPosition;
	int maxMovement;

	//overridden function
	void renderObject(SDL_Rect renderLocation);
};
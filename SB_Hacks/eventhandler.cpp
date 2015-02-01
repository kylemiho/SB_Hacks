#include "stdafx.h"
#include "eventhandler.h"

EventHandler::EventHandler()
{
	for (unsigned i = 0; i < 256; i++)
		keys[i] = false;
	mouseClicked = false;
	clickingAllowed = true; 
}

EventHandler::~EventHandler()
{

}

void EventHandler::setMouseClick(bool click)
{
	mouseClicked = click;
}

Vector2 EventHandler::getMousePosition() const
{
	return mousePosition;
}

bool EventHandler::getMouseClick() const
{
	return mouseClicked;
}

void EventHandler::getEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
		}
		if (e.type == SDL_KEYDOWN) //returns which key is pressed and bool value
		{
			keys[e.key.keysym.sym] = true;
			noKeyPressed = false;
		}
		if (e.type == SDL_KEYUP) //returns lifting finger off key and bool value
		{
			keys[e.key.keysym.sym] = false;
			noKeyPressed = true;
		}

		//mouse events
		if ((e.type == SDL_MOUSEMOTION) || (e.type == SDL_MOUSEBUTTONDOWN) || (e.type == SDL_MOUSEBUTTONUP))
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			mousePosition.x = x;
			mousePosition.y = y;
			if ((e.type == SDL_MOUSEBUTTONDOWN) && clickingAllowed) //used to prevent holding down mouse from triggering multiple events
			{
				mouseClicked = true;
				clickingAllowed = false;
			}
			if (e.type == SDL_MOUSEBUTTONUP) //resets mouse when finger is lifted
			{
				mouseClicked = false;
				clickingAllowed = true;
			}
		}
	}
}

bool EventHandler::isKeyDown(SDL_Keycode key)
{
	return keys[key];
}

bool EventHandler::isKeyUp()
{
	return noKeyPressed;
}
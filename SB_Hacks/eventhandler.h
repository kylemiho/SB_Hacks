#pragma once
#include <SDL.h>
#include <iostream>
#include "Vector2.h"
class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	void getEvent();
	bool isKeyDown(SDL_Keycode key);
	bool isKeyUp();
	bool noKeyIsPressed()
	{
		return noKeyPressed;
	}
	Vector2 getMousePosition() const;
	bool getMouseClick() const;
	void setMouseClick(bool click);
	

protected:
	bool keys[256];
	bool noKeyPressed;
	bool mouseClicked;
	bool clickingAllowed; //determines if computer should read mouse clicks or not
	Vector2 mousePosition;
};

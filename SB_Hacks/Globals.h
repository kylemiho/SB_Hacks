#pragma once
#include <SDL.h>
#include "eventhandler.h"

namespace globals
{
	extern SDL_Window *window;
	extern SDL_Renderer *renderer;
	extern SDL_Surface *gScreenSurface;
	extern EventHandler *handler;

}
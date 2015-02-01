// SB_Hacks.cpp : Defines the entry point for the console application.
//

//files to include
#include "stdafx.h"
#include "Globals.h"
#include "Object.h"
#include "Scene.h"

//libraries to include
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>

//initialize SDL dimensions
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int _tmain(int argc, _TCHAR* argv[])
{
	//bool value for quit
	bool quit = false;
	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized\n";
		return 0;
	}
	else
	{
		//initialize global variables
		globals::window = SDL_CreateWindow("SB Hacks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		globals::renderer = SDL_CreateRenderer(globals::window, -1, 0); //creates renderer, which we need to actually draw to the screen
		SDL_SetRenderDrawColor(globals::renderer, 0, 0, 0, 0); //draws black background onto the screen
		globals::handler = new EventHandler;
	}
	if (!(globals::window))
	{
		//end if window is not creates
		std::cout << "Window could not be created\n";
		return 0;
	}
	int imgFlags = IMG_INIT_PNG; //initializes flags for PNG files
	if (!IMG_Init(imgFlags) &imgFlags)
	{
		std::cout << "Failed to initialize PNG loading.\n";
		quit = true;
	}
	else
	{
		std::cout << "PNG loading success\n";
		globals::gScreenSurface = SDL_GetWindowSurface(globals::window);
	}
	//initializes SDL_mixer
	if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0))
	{
		std::cout << "Failed to initialize SDL_mixer\n";
		quit = true;
	}
		//start of while loop
	Scene *testScene = new Scene(15,15);
	testScene->initializeScene();
	std::cout << "Scene Initialized\n";
	while (!quit)
	{
		SDL_RenderClear(globals::renderer);
		globals::handler->getEvent();

		testScene->runScene();
		SDL_RenderPresent(globals::renderer);
	}

	

	SDL_DestroyWindow(globals::window);
	return 0;
}


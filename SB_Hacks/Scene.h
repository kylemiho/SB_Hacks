#pragma once
#include <SDL.h>
#include "Object.h"
#include "Globals.h"
#include <vector>
#include "Unit.h"

//variables that unit uses for object positions as well


class Scene
{
protected:
	int tileSize;
	int boardOffset;

	void addUnit(Unit *unit);
	void addTile(Object* object);
	void addMovementList(Object* object);
	void drawMovementTile(const int &xPos,const int &Ypos); 
	std::vector<Unit*> unitList;
	std::vector<Object*> tileList;
	std::vector<Object*> movementList;

	int boardWidth;
	int boardHeight;
	bool movementVisible;

	std::vector<std::vector<int> > objectType; //gives information to what is in what tile
	//0 is empty
	//1 is object
	//2 is blocked terrain
	
	int sceneState;
	//0 nothing clicked
	//1 unit clicked

	//used with movement function
	int mouseStartX;
	int mouseStartY;

public:
	Scene(int boardWidth, int boardHeight);
	~Scene();
		
	void runScene();
	void movement();
	void initializeScene();
	void initializeTiles();
	void initializeObjectType(); //sets all of objectType to 0, with size length x width

	void showMovement();
	void unshowMovement();
	
};
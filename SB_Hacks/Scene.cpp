#include "stdafx.h"
#include "Scene.h"


Scene::Scene(int boardWidth, int boardHeight)
:
boardWidth(boardWidth),
boardHeight(boardHeight)
{

	tileSize = 40;
	boardOffset = 30;
	sceneState = 0;
	movementVisible = false;

	//initialize BasicTile
	Sprite* tileSprite = new Sprite(160, 100, 25, 25);
	//Add Tiles
	for (int i = 0; i < boardWidth; ++i)
	{
		for (int j = 0; j < boardHeight; ++j)
		{
			Object *tempTile = new Object(Vector2(i*tileSize+boardOffset, j*tileSize+boardOffset), Vector2(tileSize-1, tileSize-1), "Art/tiles.png", tileSprite);
			addTile(tempTile);
		}
	}
	//initialize movementTIles
	Sprite* tileSprite2 = new Sprite(100, 100, 25, 25);
	//addMovement TIles
	for (int i = 0; i < boardWidth; ++i)
	{
		for (int j = 0; j < boardHeight; ++j)
		{
			Object *tempTile = new Object(Vector2(i*tileSize + boardOffset, j*tileSize + boardOffset), Vector2(tileSize - 1, tileSize - 1), "Art/tiles.png", tileSprite2);
			addMovementList(tempTile);
		}
	}
	delete tileSprite;
	delete tileSprite2;
}

Scene::~Scene()
{
	for (unsigned i = 0; i < unitList.size(); ++i) //deallocates dynamically allocated objects
	{
		delete unitList.at(i);
	}
	for (unsigned i = 0; i < tileList.size(); ++i) //deallocates dynamically allocated objects
	{
		delete tileList.at(i);
	}
	for (unsigned i = 0; i < movementList.size(); ++i) //deallocates dynamically allocated objects
	{
		delete movementList.at(i);
	}
}

void Scene::initializeObjectType() //initialize the board to contain the info of each object as 0
{
	std::vector<int> temp;
	for (int j = 0; j < boardHeight; ++j)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < boardWidth; ++i)
	{
		objectType.push_back(temp);
	} 
}

void Scene::initializeScene() //initializes scene with objects
{
	initializeObjectType();
	Sprite *playerSprite = new Sprite(3, 2, 16, 16);
	Unit *player = new Unit(Vector2(0,0), Vector2(40, 40), "Art/sprites.png",playerSprite,5); 
	addUnit(player);
	objectType[0][0] = 1;
	delete playerSprite;
}

void Scene::showMovement() //show where player can move
{
	//initializations for convienence
	int minBoardX = 0;
	int minBoardY = 0;
	int maxBoardX = boardWidth - 1;
	int maxBoardY = boardHeight - 1;
	int maxMovement = unitList[0]->getMaxMovement();
	int currentLocationX = unitList[0]->getLocation().x;
	int currentLocationY = unitList[0]->getLocation().y;
	
	//bottom right movement
	int i = 0;
	int j = 0;
	while (i <= maxMovement)
	{
		while (i + j <= maxMovement)
		{
			if (((currentLocationX + j) >= minBoardX) && ((currentLocationX + j) <= maxBoardX)
				&& ((currentLocationY + i) >= minBoardY) && (currentLocationY + i) <= maxBoardY)//check if in bounds before drawing
			{
				drawMovementTile(currentLocationX + j, currentLocationY + i);
			}
			++j;
		}
		j = 0;
		i++;
	}

	//top right movement
	i = 0;
	j = 0;
	while (i <= maxMovement)
	{
		while (i + j <= maxMovement)
		{
			if (((currentLocationX + j) >= minBoardX) && ((currentLocationX + j) <= maxBoardX)
				&& ((currentLocationY - i) >= minBoardY) && (currentLocationY - i) <= maxBoardY)//check if in bounds before drawing
			{
				drawMovementTile(currentLocationX + j, currentLocationY - i);
			}
			++j;
		}
		j = 0;
		i++;
	}

	//top left movement
	i = 0;
	j = 0;
	while (i <= maxMovement)
	{
		while (i + j <= maxMovement)
		{
			if (((currentLocationX - j) >= minBoardX) && ((currentLocationX - j) <= maxBoardX)
				&& ((currentLocationY + i) >= minBoardY) && (currentLocationY + i) <= maxBoardY)//check if in bounds before drawing
			{
				drawMovementTile(currentLocationX - j, currentLocationY + i);
			}
			++j;
		}
		j = 0;
		i++;
	}

	//bottom left movement
	i = 0;
	j = 0;
	while (i <= maxMovement)
	{
		while (i + j <= maxMovement)
		{
			if (((currentLocationX - j) >= minBoardX) && ((currentLocationX - j) <= maxBoardX)
				&& ((currentLocationY - i) >= minBoardY) && (currentLocationY - i) <= maxBoardY)//check if in bounds before drawing
			{
				drawMovementTile(currentLocationX - j, currentLocationY - i);
			}
			++j;
		}
		j = 0;
		i++;
	}
}

void Scene::drawMovementTile(const int &xPos, const int &yPos)
{
	movementList[xPos*boardHeight + yPos]->run();
}

void Scene::movement()
{
	if (sceneState == 0)
	{
		if (globals::handler->getMouseClick())
		{
			int currentX = ((unitList[0]->getLocation().x)*tileSize); //we want to get our location in a remainder of tileSize
			int currentY = ((unitList[0]->getLocation().y)*tileSize);
			currentX = currentX - (currentX % tileSize);
			currentY = currentY - (currentY % tileSize);

			//get location of mouse
			int mouseX = (globals::handler->getMousePosition().x) - boardOffset;
			int mouseY = (globals::handler->getMousePosition().y) - boardOffset;
			mouseX = mouseX - (mouseX % tileSize);
			mouseY = mouseY - (mouseY % tileSize);

			if ((mouseX == currentX) && (mouseY == currentY))
			{
				sceneState = 1; 
				movementVisible = true;
			}
			globals::handler->setMouseClick(false);
		}
	} else if (sceneState == 1) //move player object
	{
		if (globals::handler->getMouseClick())
		{
			int currentX = ((unitList[0]->getLocation().x)*tileSize); //we want to get our location in a remainder of tileSize
			int currentY = ((unitList[0]->getLocation().y)*tileSize);
			currentX = currentX - (currentX % tileSize);
			currentY = currentY - (currentY % tileSize);

			//get location of mouse
			int mouseX = (globals::handler->getMousePosition().x) - boardOffset;
			int mouseY = (globals::handler->getMousePosition().y) - boardOffset;
			mouseX = mouseX - (mouseX % tileSize);
			mouseY = mouseY - (mouseY % tileSize);

			if ((abs((mouseX - currentX) / tileSize) + abs((mouseY - currentY) / tileSize)) <= (unitList[0]->getMaxMovement())) //check if movement is in bounds
			{
				unitList[0]->moveX((mouseX - currentX));
				unitList[0]->moveY((mouseY - currentY));

				int tempX = (mouseX - currentX) / tileSize;
				int tempY = (mouseY - currentY) / tileSize;

				//move object
				unitList[0]->addLocation(Vector2(tempX, tempY));
				globals::handler->setMouseClick(false); //reset mouse
			}
			sceneState = 0; //done with movement, scene done
			movementVisible = false;
		}
	}
}

void Scene::runScene() //calls run on each object
{
	movement();
	for (unsigned i = 0; i < tileList.size(); ++i)
	{
		tileList[i]->run();
	}
	if (movementVisible)
	{
		showMovement();
	}
	for (unsigned i = 0; i < unitList.size(); ++i)
	{
		unitList[i]->run();
	}
}

void Scene::addTile(Object *object)
{
	tileList.push_back(object);
}

void Scene::addUnit(Unit *unit) //adds object to objectList
{
	unitList.push_back(unit);
}

void Scene::addMovementList(Object* object)
{
	movementList.push_back(object);
}

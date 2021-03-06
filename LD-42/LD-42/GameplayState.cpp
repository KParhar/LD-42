#include "GameplayState.h"

//TODO
//ADD SCREEN TO SHOW CONTROLS
//IMPLEMENT MUSIC

bool GameplayState::init(int* cS, Renderer* r, Camera* c)
{
	currentState = cS;
	renderer = r;
	camera = c;

	playerSheet.loadSpritesheet("./res/PlayerSpritesheet.png",
		"./res/PlayerSpritesheetData.txt", renderer);
	
	terrainSheet.loadSpritesheet("./res/MapSpritesheet.png",
		"./res/MapSpritesheetData.txt", renderer);

	camera->setCameraPos(0, 0);
	
	//ONLY WORKS WITH 32 BIT IMAGES - MAKE SURE LEVEL IS 32 BIT
	terrain.init("./res/level2.txt");
	player.init(0, 0);
	
	inputM.init();

	//music = Mix_LoadMUS("./res/GameMusic.mp3");

	//Mix_PlayMusic(music, -1);

	return true;
}

bool GameplayState::close()
{
	return true;
}

void GameplayState::pause() {}
void GameplayState::resume() {}

void GameplayState::input(SDL_Event* event) 
{
	inputM.input(event);
	
	if (inputM.keyPressed[K_UP])
	{
		player.move(UP);
	}
	else if (inputM.keyPressed[K_DOWN])
	{
		player.move(DOWN);
	} else if (inputM.keyPressed[K_LEFT])
	{
		player.move(LEFT);
	}
	else if (inputM.keyPressed[K_RIGHT])
	{
		player.move(RIGHT);
	}

	if (inputM.keyPressed[K_W])
	{
		camera->moveCameraScreen(UP);
	}
	else if (inputM.keyPressed[K_S]) 
	{
		camera->moveCameraScreen(DOWN);
	}
	else if (inputM.keyPressed[K_A])
	{
		camera->moveCameraScreen(LEFT);
	}
	else if (inputM.keyPressed[K_D])
	{
		camera->moveCameraScreen(RIGHT);
	}
}

void GameplayState::update()
{
	player.update();
	camera->update();

	terrain.updateArea(0, 0, 5, 5);

}
void GameplayState::render()
{
	//RENDER TERRAIN
	for (int i = 0; i < terrain.getHeight() * terrain.getHeight(); i++)
	{
		int y = floor(i / terrain.getWidth());
		int x = i % terrain.getWidth();
		if ((abs(camera->getXPos() - x*TILESIZE) < (camera->getScreenWidth()) + TILESIZE) &&
			(abs(camera->getYPos() - y*TILESIZE) < (camera->getScreenHeight()) + TILESIZE))
		{
			Tile* s = terrain.getTileMap()[i];
			if (s->getID() != NULL_TILE)
			{
				renderer->renderSDLTexture(terrainSheet.getSpritesheet(), camera, x*TILESIZE, y*TILESIZE, TILESIZE, TILESIZE, terrainSheet.getSprite(s->getAnimation()->getFrame()));
			}
		}
	}

	//RENDER PLAYER
	renderer->renderSDLRectangle(camera, player.getX()*TILESIZE, player.getY()*TILESIZE, TILESIZE, TILESIZE);
}
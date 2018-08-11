#include "Terrain.h"

bool Terrain::init(std::string fPath)
{
	width = 0;
	height = 0;
	loadTileMap(fPath);
	return true;
}

void Terrain::loadTileMap(std::string fPath)
{
	std::vector<std::string> lines;

	std::ifstream mapFile(fPath);
	std::string l;
	while (std::getline(mapFile, l))
	{
		lines.push_back(l);
	}
	height = lines.size();

	for (int i = 0; i < lines.at(0).size(); i++)
	{
		if (lines.at(0)[i] == ' ') 
		{
			++width;
		}
	}
	width++;
	
	const static int W = width;
	const static int H = height;
	tileMap = new Tile*[W*H];

	printf("%d\n", width);

	//Loading tilemaps from map data
	for (int y = 0; y < height; y++) 
	{
		std::string currLine = lines.at(y);
		for (int x = 0; x < width; x++) 
		{
			std::string idStr = splitString(currLine, " ", x, width);
			printf("%s %d\n", idStr.c_str(), x);
			int id = FLOOR_TILE;

			Animation* a = new Animation;
			switch (id)
			{
			case FLOOR_TILE:
				tileMap[y*width + x] = new Tile;
				a->init(1000);
				a->addFrame(0);
				a->addFrame(2);
				tileMap[y*width + x]->init(x, y, a, false, FLOOR_TILE);
				break;

			case R_WALL_TILE:
				tileMap[y*width + x] = new Tile;
				a->init(1000);
				a->addFrame(3);
				a->addFrame(4);
				tileMap[y*width + x]->init(x, y, a, false, R_WALL_TILE);
				break;

			default:
				tileMap[y*width + x] = new Tile;
				
				a->init(1000);
				a->addFrame(0);
				tileMap[y*width + x]->init(x, y, a, false, NULL_TILE);
				break;
			}
		}
	}




	/*for (int i = 0; i < height*width; i++)
	{
		int y = floor(i / width);
		int x = i % width;

		







		if (getPixelColor(map, x, y).r == 0 && getPixelColor(map, x, y).g == 255 && getPixelColor(map, x, y).b == 0)
		{
			tileMap[i] = new Tile;
			Animation* a = new Animation;
			a->init(1000);
			a->addFrame(0);
			a->addFrame(2);
			tileMap[i]->init(x, y, a, false, FLOOR_TILE);
		}
		else
		{
			tileMap[i] = new Tile;
			Animation* a = new Animation;
			a->init(10000);
			a->addFrame(1);
			tileMap[i]->init(x, y, a, true, NULL_TILE);
		}
	}*/
}

Tile** Terrain::getTileMap()
{
	return tileMap;
}

Tile* Terrain::getTile(int x, int y)
{
	return tileMap[(y*width) + x];
}

int Terrain::getWidth()
{
	return width;
}

int Terrain::getHeight()
{
	return height;
}

void Terrain::updateArea(int x, int y, int w, int h)
{
	for (int Y = y; Y < y + h; Y++) {
		for (int X = x; X < x + w; X++) {
			tileMap[(Y*width) + X]->update();
		}
	}
}

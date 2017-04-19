#include "Zone.h"
#include <cstdlib>

Zone::Zone(int width, int height, int maxCityWidth, int maxCityHeight, int maxCities, int maxTries):
_width(width), _height(height), _MaxCityWidth(maxCityWidth), _MaxCityHeight(maxCityHeight),
_maxCities(maxCities), _maxTries(maxTries)
{	
	_tiles = new int[width * height];

	for (int ix = 0; ix < width; ++ix) {
		for (int iy = 0; iy < height; ++iy) {
			setTile(ix, iy, 0);
		}
	}

	GenerateCities(_maxTries, _maxCities);
}

Zone::~Zone()
{
	delete[] _tiles;
}

void Zone::setTile(int x, int y, int value) const {
	_tiles[x + y * _width] = value;
}

int Zone::getTile(int x, int y) const {
	return _tiles[x + y * _width];
}

bool Zone::hasCollision(int x, int y, int width, int height) {
	if (x + width >= _width || x <= 0) return true;
	if (y + height >= _height || y <= 0) return true;

	for (int ix = (x > 0)? -1: 0; ix < width + 1; ++ix) {
		for (int iy = (y > 0)? -1: 0; iy < height + 1; ++iy) {
			if (getTile(x + ix, y + iy)) return true;
		}
	}
	return false;
}

bool Zone::PlaceCity(int x, int y, int width, int height, int cityId) {
	if (!hasCollision(x, y, width, height)) {
		for (int ix = 0; ix < width; ++ix) {
			for (int iy = 0; iy < height; ++iy) {
				setTile(x + ix, y + iy, cityId);
			}
		}
		City c = City(x, y, width, height, cityId);
		cities.push_back(c);
		return true;
	}
	return false;
}


void Zone::GenerateCities(int maxTries, int maxCities) {
	int nCities = 0;
	
	for (int iTry = 0; iTry < maxTries; ++iTry) {
		//TODO: generate position
		int x = rand() % (_width - 1) + 1;
		int y = rand() % (_height -1) + 1;

		/*FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("x %d y %d \n", x, y);*/

		//TODO: generate width, height
		int width = rand() % (_MaxCityWidth - 2) + 2;
		int height = rand() % (_MaxCityHeight - 2) + 2;

		/*printf("w %d h %d \n", width, height);
		fclose(fp);*/

		if (PlaceCity(x, y, width, height, nCities + 1)) {
			++nCities;
		}

		if (nCities == maxCities) {
			FILE* fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
			printf("amount of cities(max): %d", nCities);
			fclose(fp);
			break;
		}
		if (iTry == maxTries - 1) {
			FILE* fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
			printf("maxtries \n");
			fclose(fp);
		}
	}
	printGrid();
}

void Zone::printGrid() {
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	for (int ix = 0; ix < _width; ++ix) {
		for (int iy = 0; iy < _height; ++iy) {
			printf("|%d|", getTile(ix, iy));
		}
		printf("\n");
	}
	fclose(fp);
}

#include "Zone.h"
#include <cstdlib>

Zone::Zone(int width, int depth, int maxCityWidth, int maxCityHeight, int maxCities, int maxTries):
_width(width), _depth(depth), _MaxCityWidth(maxCityWidth), _MaxCityHeight(maxCityHeight),
_maxCities(maxCities), _maxTries(maxTries)
{	
	// create grid for spawning
	_tiles = new int[width * depth];
	//set values to 0
	for (int ix = 0; ix < width; ++ix) {
		for (int iy = 0; iy < depth; ++iy) {
			setTile(ix, iy, 0);
		}
	}

	GenerateCities(_maxTries, _maxCities);
}

Zone::~Zone()
{
	//remove pointer array
	delete[] _tiles;
}

void Zone::setTile(int x, int y, int value) const {
	_tiles[x + y * _width] = value;
}

int Zone::getTile(int x, int y) const {
	return _tiles[x + y * _width];
}

/// <summary>
/// Determines whether the specified city has collision with another city.
/// </summary>
/// <param name="c">The city.</param>
/// <returns>
///   <c>true</c> if the specified c has collision; otherwise, <c>false</c>.
/// </returns>
bool Zone::hasCollision(City c) {
	if (c._x + c._width >= _width || c._x <= 0) return true;
	if (c._z + c._depth >= _depth || c._z <= 0) return true;

	for (int ix = (c._x > 0)? -1: 0; ix < c._width + 1; ++ix) {
		for (int iz = (c._z > 0)? -1: 0; iz < c._depth + 1; ++iz) {
			if (getTile(c._x + ix, c._z + iz)) return true;
		}
	}
	return false;
}

/// <summary>
/// Places a city in the grid and in the city list, if that city has no collisions at that location.
/// </summary>
/// <param name="x">The x position of the city.</param>
/// <param name="z">The z position of the city.</param>
/// <param name="width">The width of the city.</param>
/// <param name="depth">The depth of the city.</param>
/// <param name="cityId">The city identifier.</param>
/// <returns></returns>
bool Zone::PlaceCity(int x, int z, int width, int depth, int cityId) {
	City c = City(x, z, width, depth, cityId);
	if (!hasCollision(c)) {
		for (int ix = 0; ix < width; ++ix) {
			for (int iz = 0; iz < depth; ++iz) {
				setTile(x + ix, z + iz, cityId);
			}
		}
		cities.push_back(c);
		return true;
	}
	return false;
}


/// <summary>
/// Generates city positions within the grid. All cities are at least one block away from the sides and one block away from the edges.
/// </summary>
/// <param name="maxTries">The maximum amount of tries, before quiting.</param>
/// <param name="maxCities">The maximum amount of cities allowed in the zone.</param>
void Zone::GenerateCities(int maxTries, int maxCities) {
	int nCities = 0;
	
	for (int iTry = 0; iTry < maxTries; ++iTry) {
		//TODO: generate position
		int x = rand() % (_width - 1) + 1;
		int z = rand() % (_depth -1) + 1;

		//TODO: generate width, depth
		int width = rand() % (_MaxCityWidth - 2) + 2;
		int depth = rand() % (_MaxCityHeight - 2) + 2;

		if (PlaceCity(x, z, width, depth, nCities + 1)) {
			++nCities;
		}
	}
	printGrid();
}

/// <summary>
/// Prints the grid with cities/paths within zone.
/// </summary>
void Zone::printGrid() {
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	for (int ix = 0; ix < _width; ++ix) {
		for (int iy = 0; iy < _depth; ++iy) {
			printf("|%d|", getTile(ix, iy));
		}
		printf("\n");
	}
	fclose(fp);
}

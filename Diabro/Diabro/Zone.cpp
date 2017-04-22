#include "Zone.h"

Zone::Zone(int pWidth, int pDepth, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries):
_width(pWidth), _depth(pDepth), _maxCityWidth(pMaxCityWidth), _maxCityHeight(pMaxCityHeight),
_maxCities(pMaxCities), _maxTries(pMaxTries)
{	
	// create grid for spawning
	_tiles = new int[pWidth * pDepth];
	//set values to 0
	for (int ix = 0; ix < pWidth; ++ix) {
		for (int iy = 0; iy < pDepth; ++iy) {
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
	if (c.x + c.width >= _width || c.x <= 0) return true;
	if (c.z + c.depth >= _depth || c.z <= 0) return true;

	for (int ix = (c.x > 0)? -1: 0; ix < c.width + 1; ++ix) {
		for (int iz = (c.z > 0)? -1: 0; iz < c.depth + 1; ++iz) {
			if (getTile(c.x + ix, c.z + iz)) return true;
		}
	}
	return false;
}

/// <summary>
/// Places a city in the grid and in the city list, if that city has no collisions at that location.
/// </summary>
/// <param name="pX">The pX position of the city.</param>
/// <param name="pZ">The pZ position of the city.</param>
/// <param name="pWidth">The pWidth of the city.</param>
/// <param name="pDepth">The pDepth of the city.</param>
/// <param name="cityId">The city identifier.</param>
/// <returns></returns>
bool Zone::PlaceCity(int pX, int pZ, int pWidth, int pDepth, int pCityId) {
	City c = City(pX, pZ, pWidth, pDepth, pCityId);
	if (!hasCollision(c)) {
		for (int ix = 0; ix < pWidth; ++ix) {
			for (int iz = 0; iz < pDepth; ++iz) {
				setTile(c.x + ix, c.z + iz, c.id);
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
/// <param name="pMaxTries">The maximum amount of tries, before quiting.</param>
/// <param name="pMaxCities">The maximum amount of cities allowed in the zone.</param>
void Zone::GenerateCities(int maxTries, int maxCities) {
	int nCities = 0;
	
	for (int iTry = 0; iTry < maxTries; ++iTry) {
		//TODO: generate position
		int x = rand() % (_width - 1) + 1;
		int z = rand() % (_depth -1) + 1;

		//TODO: generate pWidth, pDepth
		int width = rand() % (_maxCityWidth - 2) + 2;
		int depth = rand() % (_maxCityHeight - 2) + 2;

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

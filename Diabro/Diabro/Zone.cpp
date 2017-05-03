#include "Zone.h"
#include <ctime>
#include "GameManager.h"

#include <OgreConfigFile.h>


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

void Zone::setTile(int pX, int pY, int pValue) const {
	_tiles[pX + pY * _width] = pValue;
}

int Zone::getTile(int pX, int pY) const {
	return _tiles[pX + pY * _width];
}

/// <summary>
/// Determines whether the specified city has collision with another city.
/// </summary>
/// <param name="pC">The city.</param>
/// <returns>
///   <pC>true</pC> if the specified pC has collision; otherwise, <pC>false</pC>.
/// </returns>
bool Zone::hasCollision(City pC) {
	if (pC.x + pC.width >= _width || pC.x <= 0) return true;
	if (pC.z + pC.depth >= _depth || pC.z <= 0) return true;

	for (int ix = (pC.x > 0)? -1: 0; ix < pC.width + 1; ++ix) {
		for (int iz = (pC.z > 0)? -1: 0; iz < pC.depth + 1; ++iz) {
			if (getTile(pC.x + ix, pC.z + iz)) return true;
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
	City c = City(pX, pZ, pWidth, pDepth, pCityId, 1000);
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
void Zone::GenerateCities(int pMaxTries, int pMaxCities) {
	int nCities = 0;
	srand(time(NULL));

	for (int iTry = 0; iTry < pMaxTries; ++iTry) {
		//TODO: generate position not random
		int x = rand() % (_width - 1) + 1;
		int z = rand() % (_depth -1) + 1;
		
		//TODO: generate pWidth, pDepth not random
		int width = rand() % (_maxCityWidth - 2) + 2;
		int depth = rand() % (_maxCityHeight - 2) + 2;

		if (PlaceCity(x, z, width, depth, nCities + 1)) {
			++nCities;
		}
		if (nCities == pMaxCities) {
			break;
		}
	}
}

/// <summary>
/// Prints the grid with cities/paths within zone.
/// </summary>
void Zone::printGrid() {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	for (int ix = 0; ix < _width; ++ix) {
		for (int iy = 0; iy < _depth; ++iy) {
			printf("|%d|", getTile(ix, iy));
		}
		printf("\n");
	}
	fclose(fp);
#endif
}

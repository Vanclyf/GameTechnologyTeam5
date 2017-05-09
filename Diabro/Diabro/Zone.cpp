#include "Zone.h"
#include <ctime>
#include <OgreConfigFile.h>
#include <OgreMath.h>

Zone::Zone() {
	
}


Zone::Zone(int pWidth, int pDepth, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries):
_width(pWidth), _depth(pDepth), _maxCityWidth(pMaxCityWidth), _maxCityHeight(pMaxCityHeight)
{	
	// create grid for spawning
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("create tile component...");
#endif
	_tiles = new int[pWidth * pDepth];
	//set values to 0
	for (int ix = 0; ix < pWidth; ++ix) {
		for (int iy = 0; iy < pDepth; ++iy) {
			setTile(ix, iy, 0);
		}
	}
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	printf("generate cities...");
#endif
	generateCities(pMaxTries, pMaxCities);
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	printf("generate paths...");
#endif
	int n = generatePathways(cities.size() + 1);
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	printf("connecting dungeon...");
#endif
	connectDungeon(cities.size() + 1 + n, 0.5f);
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	printf("cleaning and printing...\n");
	fclose(fp);
#endif
	cleanGrid();
	printGrid();
}

Zone::~Zone()
{
	//remove pointer array
	//delete[] _tiles;
}

void Zone::cleanGrid()
{
	for (int ix = 0; ix < _width; ++ix)
	{
		for (int iz = 0; iz < _depth; ++iz)
		{
			if (getTile(ix, iz) <= 0)
			{
				setTile(ix, iz, 0);
			}
			else
			{
				setTile(ix, iz, 1);
			}
		}
	}
}


void Zone::setTile(int pX, int pY, int pValue) const {
	_tiles[pX + pY * _width] = pValue;
}

void Zone::setTile(Coordinate pCoord, int pValue) const {
	_tiles[pCoord.x + pCoord.z * _width] = pValue;
}


int Zone::getTile(int pX, int pY) const {
	return _tiles[pX + pY * _width];
}

int Zone::getTile(Coordinate pCoord) const {
	return _tiles[pCoord.x + pCoord.z * _width];
}


Coordinate Zone::getPosition(int pId, bool pCheckNeighbours) {
	std::vector<Coordinate> positions;

	for (int ix = 1; ix < _width - 1; ++ix) {
		for (int iz = 1; iz < _depth - 1; ++iz) {
			if(getTile(ix, iz) == pId) {
				if (pCheckNeighbours) {
					if( getTile(ix - 1, iz - 1) == pId &&
						getTile(ix    , iz - 1) == pId &&
						getTile(ix + 1, iz - 1) == pId &&
						getTile(ix - 1, iz    ) == pId &&
						getTile(ix + 1, iz    ) == pId &&
						getTile(ix - 1, iz + 1) == pId &&
						getTile(ix    , iz + 1) == pId &&
						getTile(ix + 1, iz + 1) == pId) {
						positions.push_back(Coordinate(ix, iz));
					}
				}
				else {
					positions.push_back(Coordinate(ix, iz));
				}
			}
		}
	}
	if (positions.size() > 0) {
		int iRand = rand() % positions.size();
		return positions[iRand];
	} else {
		return Coordinate(-1, -1);
	}
	
}

void Zone::connectDungeon(int pId, float pChance) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("start connectDungeon : \n");

	//TODO find all possible connections
	//connect rooms to path 1
	//if more than one path excists, connect other paths to
	std::vector<std::pair<Coordinate, int>> connections;

	for (int i = 0; i < cities.size(); ++i) {

		int rndIndex[2] = { 0,0 };
		int start = connections.size();
		int length = getPossibleConnections(cities[i], &connections);
		printf(">> city: %d connections{ start:%d, length:%d }  \n", i, start, length);

		if (length < 1) continue;

		rndIndex[0] = rand() % length + start;
		printf(">> generated random %d, list size %d  \n", rndIndex[0], connections.size());
		//TODO: open some connections, so that all of the dungeon is connected
		setTile(connections[rndIndex[0]].first, connections[rndIndex[0]].second);
		cities[i].connections.push_back(connections[rndIndex[0]].first);
		connections.erase(connections.begin() + rndIndex[0]);
		printf(">> removed carved connection\n");
		length--;

		//TODO: open random connections, so that the dungeon is not perfect anymore
		if (length > 1) {
			float rndPercent = (rand() % 100 + 1) / 100.0f;
			if (rndPercent <= pChance) {
				rndIndex[1] = rndIndex[0];
				while (rndIndex[1] == rndIndex[0]) {
					rndIndex[1] = rand() % length + start;
					printf(">>> generated new second random %d \n", rndIndex[1]);
				}
				setTile(connections[rndIndex[1]].first, connections[rndIndex[1]].second);
				cities[i].connections.push_back(connections[rndIndex[1]].first);
				connections.erase(connections.begin() + rndIndex[1]);
				printf(">>> removed second carved connections\n");
			}
		}
	}
	printf("\n regions:");
	int regions = changeTileValues(pId);
	if (!connections.empty() && regions > 1){
		std::vector<std::pair<Coordinate, int>> options;
		for (int i = 0; i < connections.size(); ++i) {
			if ((getTile(connections[i].first.x, connections[i].first.z + 1) > 2 && getTile(connections[i].first.x, connections[i].first.z - 1) == 2) ||
				(getTile(connections[i].first.x, connections[i].first.z + 1) == 2 && getTile(connections[i].first.x, connections[i].first.z - 1) > 2)) {
				options.push_back(std::make_pair(connections[i].first, connections[i].second));
				connections.erase(connections.begin() + i);
			} else if ((getTile(connections[i].first.x + 1, connections[i].first.z) > 2 && getTile(connections[i].first.x - 1, connections[i].first.z) == 2) ||
				(getTile(connections[i].first.x + 1, connections[i].first.z) == 2 && getTile(connections[i].first.x - 1, connections[i].first.z) > 2)) {
				options.push_back(std::make_pair(connections[i].first, connections[i].second));
				connections.erase(connections.begin() + i);
			}
		}

		int regions = changeTileValues(pId);
		//printGrid();
		while (regions > 1 && options.size() > 0) {
			//TODO: open options
			int rnd = rand() % options.size();
			setTile(options[rnd].first, 1);
			cities[options[rnd].second].connections.push_back(options[rnd].first);

			options.erase(options.begin() + rnd);
			//TODO: check if whole dungeon is reachable
			regions = changeTileValues(pId);
		}
	}
	//printGrid();
	fclose(fp);
#endif
}

void Zone::printValues() {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	int values[100];

	for (int ix = 0; ix < _width; ++ix) {
		for (int iz = 0; iz < _depth; ++iz) {
			int n = getTile(ix, iz);
			if (n > 0) {
				values[n] = n;
			}
		}
	}
	for (int i = 1; i < 100; ++i) {
		if (values[i] > 0) {
			printf("%d, ", values[i]);
		}
		
	}
	printf("\n");
	fclose(fp);
#endif
}

Coordinate Zone::getResolution() const {
	return(Coordinate(_width, _depth));
}


int Zone::changeTileValues(int pMaxIndex) {
	
	int currentRegion = 1;
	int amountOfRegions = 0;
	for (int i = 1; i <= pMaxIndex; ++i) {
		std::vector<Coordinate> positions;
		//pick random cell for current region
		positions.push_back(getPosition(currentRegion, false));
		
		if (getTile(positions[0]) != currentRegion) {
			positions.clear();
			currentRegion++;
			continue;
		}
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("position = %d, %d (%d) \n", positions[0].x, positions[0].z, getTile(positions[0]));
		fclose(fp);
#endif

		if (positions[0].x >= 0 && positions[0].z >= 0) {
			while(!positions.empty()) {
				//find all neighbours (which are >0)
				//and add them to the list
				if (positions[0].z + 1 < _depth - 1) {
					if (getTile(positions[0].x, positions[0].z + 1) > 0) positions.push_back(Coordinate(positions[0].x, positions[0].z + 1));
				}
				if (positions[0].x + 1 < _width - 1) {
					if (getTile(positions[0].x + 1, positions[0].z) > 0) positions.push_back(Coordinate(positions[0].x + 1, positions[0].z));
				}
				if (positions[0].z > 0) {
					if (getTile(positions[0].x, positions[0].z - 1) > 0) positions.push_back(Coordinate(positions[0].x, positions[0].z - 1));
				}
				if (positions[0].x - 1 > 0) {
					if (getTile(positions[0].x - 1, positions[0].z) > 0) positions.push_back(Coordinate(positions[0].x - 1, positions[0].z));
				}
				
				//cr value to cell
				setTile(positions[0], -(amountOfRegions + 2));
				positions.erase(positions.begin());
			}
			amountOfRegions++;
		}
		positions.clear();
		currentRegion++;
		//remove last position
	}
	for (int ix = 0; ix < _width; ++ix) {
		for (int iz = 0; iz < _depth; ++iz) {
			int n = getTile(ix, iz);
			if (n < 0 && n != -1) {
				setTile(ix, iz, getTile(ix, iz) * -1);
			}
		}
	}
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("amount of regions: %d \n", amountOfRegions);
	fclose(fp);
#endif
	return amountOfRegions;
}


int Zone::getPossibleConnections(City pCity, std::vector<std::pair<Coordinate, int>> *connections) {
	int connectionAmount = 0;
	for (int ix = 0; ix < pCity.width; ++ix) {
		for (int iz = 0; iz < pCity.depth; ++iz) {
			//north
			if (getTile(pCity.position.x + ix, pCity.position.z + iz - 1) == 0 && pCity.position.z + iz - 2 > 0) {
				if (getTile(pCity.position.x + ix, pCity.position.z + iz - 2) > 0) {
					connections->push_back(std::make_pair(Coordinate(pCity.position.x + ix, pCity.position.z + iz - 1), pCity.id));
					setTile(pCity.position.x + ix, pCity.position.z + iz - 1, -1);
					connectionAmount++;
				}
			}
			//east
			if (getTile(pCity.position.x + ix + 1, pCity.position.z + iz) == 0 && pCity.position.x + ix + 2 < _width) {
				if (getTile(pCity.position.x + ix + 2, pCity.position.z + iz) > 0) {
					connections->push_back(std::make_pair(Coordinate(pCity.position.x + ix + 1, pCity.position.z + iz), pCity.id));
					setTile(pCity.position.x + ix + 1, pCity.position.z + iz, -1);
					connectionAmount++;
				}
			}
			//south
			if (getTile(pCity.position.x + ix, pCity.position.z + iz + 1) == 0 && pCity.position.z + iz + 2 < _depth) {
				if (getTile(pCity.position.x + ix, pCity.position.z + iz + 2) > 0) {
					connections->push_back(std::make_pair(Coordinate(pCity.position.x + ix, pCity.position.z + iz + 1), pCity.id));
					setTile(pCity.position.x + ix, pCity.position.z + iz + 1, -1);
					connectionAmount++;
				}
			}
			//west
			if (getTile(pCity.position.x + ix - 1, pCity.position.z + iz) == 0 && pCity.position.x + ix - 2 > 0) {
				if (getTile(pCity.position.x + ix - 2, pCity.position.z + iz) > 0) {
					connections->push_back(std::make_pair(Coordinate(pCity.position.x + ix - 1, pCity.position.z + iz), pCity.id));
					setTile(pCity.position.x + ix - 1, pCity.position.z + iz, -1);
					connectionAmount++;
				}
			}
		}
	}
	return connectionAmount;
}


int Zone::generatePathways(int pPathId) {
	int nIterations = 0;
	while (!checkGrid()) {
		std::vector<Coordinate> cellList;

		//Possible improvement: pass startpos to method to use heuristic for shapes
		//generate random empty pPosition
		Coordinate position = getPosition(0, true);
		(position.x % 2 == 0) ? position.x++ : position.x;
		(position.z % 2 == 0) ? position.z++ : position.z;

		cellList.push_back(Coordinate(position.x, position.z));
		int current = 0;
		setTile(cellList[current].x, cellList[current].z, -1); // all cells in celllist are marked as -1

		while (!cellList.empty()) {
			if (hasNeighBours(cellList[current])) {
				cellList.push_back(getRndNeighbour(cellList[current], pPathId + nIterations));
				++current;
				setTile(cellList[current].x, cellList[current].z, -1);
			}
			else {
				setTile(cellList[current].x, cellList[current].z, pPathId + nIterations);
				cellList.erase(cellList.begin() + current);
				--current;
				//TODO: implement heuristic for new current
			}
		}
		nIterations++;
	}
	return nIterations;
}

Coordinate Zone::getRndNeighbour(Coordinate pCell, int nPathId) {
	std::vector<Coordinate> neighbours = getNeighbours(pCell);
	int i = rand() % neighbours.size();
	Coordinate difference = neighbours[i];
	
	difference.x = difference.x - pCell.x;
	difference.z = difference.z - pCell.z;

	//mark the cell in between current and next cell as drawn
	if (difference.x == 0) {
		(difference.z > 0) ? setTile(pCell.x, pCell.z + 1, nPathId) : setTile(pCell.x, pCell.z - 1, nPathId);
	}
	else {
		(difference.x > 0) ? setTile(pCell.x + 1, pCell.z, nPathId) : setTile(pCell.x - 1, pCell.z, nPathId);
	}	

	return (Coordinate(neighbours[i]));	
}

std::vector<Coordinate> Zone::getNeighbours(Coordinate pCell) {
	std::vector<Coordinate> neighbours;
	if (!getTile(pCell.x, pCell.z + 2) && !(pCell.z + 2 >= _depth - 1)) neighbours.push_back(Coordinate(pCell.x, pCell.z + 2));
	if (!getTile(pCell.x + 2, pCell.z) && !(pCell.x + 2 >= _width - 1)) neighbours.push_back(Coordinate(pCell.x + 2, pCell.z));
	if (!getTile(pCell.x - 2, pCell.z) && !(pCell.x - 2 <= 0)) neighbours.push_back(Coordinate(pCell.x - 2, pCell.z));
	if (!getTile(pCell.x, pCell.z - 2) && !(pCell.z - 2 <= 0)) neighbours.push_back(Coordinate(pCell.x, pCell.z - 2));
	return (neighbours);
}

bool Zone::hasNeighBours(Coordinate pCell) {
	if (!getTile(pCell.x, pCell.z + 2) && !(pCell.z + 2 >= _depth - 1)) return true;
	if (!getTile(pCell.x + 2, pCell.z) && !(pCell.x + 2 >= _width - 1)) return true;
	if (!getTile(pCell.x - 2, pCell.z) && !(pCell.x - 2 <= 0)) return true;
	if (!getTile(pCell.x, pCell.z - 2) && !(pCell.z - 2 <= 0)) return true;
	return false;
}

bool Zone::hasCollision(Coordinate pPosition) {
	return(getTile(pPosition.x, pPosition.z) ? true : false);
}

/// <summary>
/// Determines whether the specified city has collision with another city.
/// </summary>
/// <param name="pC">The city.</param>
/// <returns>
///   <pC>true</pC> if the specified pC has collision; otherwise, <pC>false</pC>.
/// </returns>
bool Zone::hasCollision(City pC) {
	if (pC.position.x + pC.width >= _width || pC.position.x <= 0) return true;
	if (pC.position.z + pC.depth >= _depth || pC.position.z <= 0) return true;

	for (int ix = (pC.position.x > 0)? -1: 0; ix < pC.width + 1; ++ix) {
		for (int iz = (pC.position.z > 0)? -1: 0; iz < pC.depth + 1; ++iz) {
			if (getTile(pC.position.x + ix, pC.position.z + iz)) return true;
		}
	}
	return false;
}

bool Zone::checkGrid() {
	for (int iX = 1; iX < _width; iX += 2) {
		for (int iZ = 1; iZ < _depth; iZ +=2) {
			if (getTile(iX, iZ) == 0) {
				return false;
			}
		}
	}
	return true;
}


/// <summary>
/// Places a city in the grid and in the city list, if that city has no collisions at that location.
/// </summary>
/// <param name="pX">The pX pPosition of the city.</param>
/// <param name="pZ">The pZ pPosition of the city.</param>
/// <param name="pWidth">The pWidth of the city.</param>
/// <param name="pDepth">The pDepth of the city.</param>
/// <param name="cityId">The city identifier.</param>
/// <returns></returns>
bool Zone::placeCity(City pC) {
	if (!hasCollision(pC)) {
		for (int ix = 0; ix < pC.width; ++ix) {
			for (int iz = 0; iz < pC.depth; ++iz) {
				setTile(pC.position.x + ix, pC.position.z + iz, pC.id);
			}
		}
		cities.push_back(pC);
		return true;
	}
	return false;
}


/// <summary>
/// Generates city positions within the grid. All cities are at least one block away from the sides and one block away from the edges.
/// </summary>
/// <param name="pMaxTries">The maximum amount of tries, before quiting.</param>
/// <param name="pMaxCities">The maximum amount of cities allowed in the zone.</param>
void Zone::generateCities(int pMaxTries, int pMaxCities) {
	int nCities = 0;
	srand(time(NULL));

	for (int iTry = 0; iTry < pMaxTries; ++iTry) {
		//TODO: generate width, depth not random
		int width = rand() % (_maxCityWidth - 2) + 2;
		int depth = rand() % (_maxCityHeight - 2) + 2;
		//make width and height uneven
		(width % 2 == 0) ? width++ : width;
		(depth % 2 == 0) ? depth++ : depth;

		//TODO: generate position not random
		int x = rand() % (_width - width - 1) + 1;
		int z = rand() % (_depth - depth - 1) + 1;
		//make pPosition even
		(x % 2 == 0) ? x++ : x;
		(z % 2 == 0) ? z++ : z;

		if (placeCity(City(x, z, width, depth, nCities + 1))) {
			++nCities;
		}
		if (nCities >= pMaxCities) {
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
			printf((getTile(ix, iy) < 10 && getTile(ix, iy) >= 0)?"| " : "|");
			printf("%d|", getTile(ix, iy));
		}
		printf("\n");
	}
	fclose(fp);
	printValues();
#endif
}

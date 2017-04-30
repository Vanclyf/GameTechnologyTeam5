#include "Zone.h"
#include <ctime>
#include "math.h"
#include <OgreConfigFile.h>
#include <OgreMath.h>


Zone::Zone(int pWidth, int pDepth, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries):
_width(pWidth), _depth(pDepth), _maxCityWidth(pMaxCityWidth), _maxCityHeight(pMaxCityHeight)
{	
	// create grid for spawning
	_tiles = new int[pWidth * pDepth];
	//set values to 0
	for (int ix = 0; ix < pWidth; ++ix) {
		for (int iy = 0; iy < pDepth; ++iy) {
			setTile(ix, iy, 0);
		}
	}

	generateCities(pMaxTries, pMaxCities);

	int n = generatePathways(cities.size() + 1);

	connectDungeon(cities.size() + 1 + n, 0.5f);
}

Zone::~Zone()
{
	//remove pointer array
	delete[] _tiles;
}

void Zone::setTile(int pX, int pY, int pValue) const {
	_tiles[pX + pY * _width] = pValue;
}

void Zone::setTile(coordinate pCoord, int pValue) const {
	_tiles[pCoord.x + pCoord.z * _width] = pValue;
}


int Zone::getTile(int pX, int pY) const {
	return _tiles[pX + pY * _width];
}

int Zone::getTile(coordinate pCoord) const {
	return _tiles[pCoord.x + pCoord.z * _width];
}


coordinate Zone::getPosition(int pId, bool pCheckNeighbours) {
	std::vector<coordinate> positions;

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
						positions.push_back(coordinate(ix, iz));
					}
				}
				else {
					positions.push_back(coordinate(ix, iz));
				}
			}
		}
	}
	if (positions.size() > 0) {
		int iRand = rand() % positions.size();
		return positions[iRand];
	} else {
		return coordinate(-1, -1);
	}
	
}

void Zone::connectDungeon(int pId, float pChance) {
	//TODO find all possible connections
	//connect rooms to path 1
	//if more than one path excists, connect other paths to
	std::vector<std::pair<coordinate, int>> connections;
	connections.push_back(std::make_pair(coordinate(1, 1), 1));
	for (int i = 0; i < cities.size(); ++i) {

		int rndIndex[2] = { 0,0 };
		int start = connections.size();

		int length = getPossibleConnections(cities[i], &connections);
	
		rndIndex[0] = rand() % length + start;

		//TODO: open some connections, so that all of the dungeon is connected
		setTile(connections[rndIndex[0]].first, connections[rndIndex[0]].second);
		cities[i].connections.push_back(connections[rndIndex[0]].first);
		connections.erase(connections.begin() + rndIndex[0]);
		length--;
		start--;

		//TODO: open random connections, so that the dungeon is not perfect anymore
		if (length > 1) {
			float rndPercent = (rand() % 100 + 1) / 100.0f;
			if (rndPercent <= pChance) {
				rndIndex[1] = rndIndex[0];
				while (rndIndex[1] == rndIndex[0]) {
					rndIndex[1] = rand() % length + start;
				}
				setTile(connections[rndIndex[1]].first, connections[rndIndex[1]].second);
				cities[i].connections.push_back(connections[rndIndex[1]].first);
				connections.erase(connections.begin() + rndIndex[1]);
			}
		}
	}
	
	int regions = changeTileValues(pId); 
	printGrid();
	
	if (regions > 1) {
		std::vector<std::pair<coordinate, int>> options;
		
		for (int i = 0; i < connections.size(); ++i) {
			if ((getTile(connections[i].first.x, connections[i].first.z + 1) > 2 && getTile(connections[i].first.x, connections[i].first.z - 1) == 2) ||
				(getTile(connections[i].first.x, connections[i].first.z + 1) == 2 && getTile(connections[i].first.x, connections[i].first.z - 1) > 2)) {
				options.push_back(std::make_pair(connections[i].first, connections[i].second));
			}
			if ((getTile(connections[i].first.x + 1, connections[i].first.z) > 2 && getTile(connections[i].first.x - 1, connections[i].first.z) == 2) ||
				(getTile(connections[i].first.x + 1, connections[i].first.z) == 2 && getTile(connections[i].first.x - 1, connections[i].first.z) > 2)) {
				options.push_back(std::make_pair(connections[i].first, connections[i].second));
			}
		}

		if (options.size() < 1) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			FILE* fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
			printf("no options found \n");
			fclose(fp);
#endif
		}
		if (options.size() >= 1) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			FILE* fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
			printf("options: %d, %d \n", options[0].first.z, options[0].first.x);
			fclose(fp);
#endif
		}
		/*else {
			int n = (3 > options.size()) ? 3 : options.size();
			for (int i = 0; i < n; ++i) {
				int rnd = rand() % options.size();
				setTile(options[rnd].first, 1);
				cities[options[rnd].second].connections.push_back(options[rnd].first);
			}
		}*/
		regions = changeTileValues(regions);
		printGrid();
	}
	//TODO: check if whole dungeon is reachable
}

int Zone::changeTileValues(int pMaxIndex) {
	
	int currentRegion = 1;
	int amountOfRegions = 1;
	for (int i = 1; i <= pMaxIndex; ++i) {
		std::vector<coordinate> positions;
		//pick random cell for current region
		positions.push_back(getPosition(currentRegion, false));

		if (positions[0].x >= 0 && positions[0].z >= 0) {
			while(!positions.empty()) {
				//find all neighbours (which are >0)
				//and add them to the list
				if (getTile(positions[0].x, positions[0].z + 1) > 0) positions.push_back(coordinate(positions[0].x, positions[0].z + 1));
				if (getTile(positions[0].x + 1, positions[0].z) > 0) positions.push_back(coordinate(positions[0].x + 1, positions[0].z));
				if (getTile(positions[0].x, positions[0].z - 1) > 0) positions.push_back(coordinate(positions[0].x, positions[0].z - 1));
				if (getTile(positions[0].x - 1, positions[0].z) > 0) positions.push_back(coordinate(positions[0].x - 1, positions[0].z));
				
				//cr value to cell
				setTile(positions[0], -(amountOfRegions + 1));
				positions.erase(positions.begin());
			}
			currentRegion++;
			amountOfRegions++;
		}
		else {
			positions.clear();
			currentRegion++;
			//remove last position
		}
	}
	for (int ix = 0; ix < _width; ++ix) {
		for (int iz = 0; iz < _depth; ++iz) {
			if (getTile(ix, iz) < 0 && getTile(ix, iz) != -1) {
				setTile(ix, iz, getTile(ix, iz) * -1);
			}
		}
	}
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("amount of regions: %d \n", amountOfRegions - 1);
	fclose(fp);
#endif
	return amountOfRegions - 1;
}


int Zone::getPossibleConnections(City pCity, std::vector<std::pair<coordinate, int>> *connections) {
	int connectionAmount = 0;
	for (int ix = 0; ix < pCity.width; ++ix) {
		for (int iz = 0; iz < pCity.depth; ++iz) {
			//north
			if (getTile(pCity.position.x + ix, pCity.position.z + iz - 1) == 0 && pCity.position.z + iz - 2 > 0) {
				if (getTile(pCity.position.x + ix, pCity.position.z + iz - 2) > 0) {
					connections->push_back(std::make_pair(coordinate(pCity.position.x + ix, pCity.position.z + iz - 1), pCity.id));
					setTile(pCity.position.x + ix, pCity.position.z + iz - 1, -1);
					connectionAmount++;
				}
			}
			//east
			if (getTile(pCity.position.x + ix + 1, pCity.position.z + iz) == 0 && pCity.position.x + ix + 2 < _width) {
				if (getTile(pCity.position.x + ix + 2, pCity.position.z + iz) > 0) {
					connections->push_back(std::make_pair(coordinate(pCity.position.x + ix + 1, pCity.position.z + iz), pCity.id));
					setTile(pCity.position.x + ix + 1, pCity.position.z + iz, -1);
					connectionAmount++;
				}
			}
			//south
			if (getTile(pCity.position.x + ix, pCity.position.z + iz + 1) == 0 && pCity.position.z + iz + 2 < _depth) {
				if (getTile(pCity.position.x + ix, pCity.position.z + iz + 2) > 0) {
					connections->push_back(std::make_pair(coordinate(pCity.position.x + ix, pCity.position.z + iz + 1), pCity.id));
					setTile(pCity.position.x + ix, pCity.position.z + iz + 1, -1);
					connectionAmount++;
				}
			}
			//west
			if (getTile(pCity.position.x + ix - 1, pCity.position.z + iz) == 0 && pCity.position.x + ix - 2 > 0) {
				if (getTile(pCity.position.x + ix - 2, pCity.position.z + iz) > 0) {
					connections->push_back(std::make_pair(coordinate(pCity.position.x + ix - 1, pCity.position.z + iz), pCity.id));
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
		std::vector<coordinate> cellList;

		//Possible improvement: pass startpos to method to use heuristic for shapes
		//generate random empty pPosition
		coordinate position = getPosition(0, true);
		(position.x % 2 == 0) ? position.x++ : position.x;
		(position.z % 2 == 0) ? position.z++ : position.z;

		cellList.push_back(coordinate(position.x, position.z));
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
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("iterations: %d \n", nIterations);
	fclose(fp);
#endif
	return nIterations;
}

coordinate Zone::getRndNeighbour(coordinate pCell, int nPathId) {
	std::vector<coordinate> neighbours = getNeighbours(pCell);
	int i = rand() % neighbours.size();
	coordinate difference = neighbours[i];
	
	difference.x = difference.x - pCell.x;
	difference.z = difference.z - pCell.z;

	//mark the cell in between current and next cell as drawn
	if (difference.x == 0) {
		(difference.z > 0) ? setTile(pCell.x, pCell.z + 1, nPathId) : setTile(pCell.x, pCell.z - 1, nPathId);
	}
	else {
		(difference.x > 0) ? setTile(pCell.x + 1, pCell.z, nPathId) : setTile(pCell.x - 1, pCell.z, nPathId);
	}	

	return (coordinate(neighbours[i]));	
}

std::vector<coordinate> Zone::getNeighbours(coordinate pCell) {
	std::vector<coordinate> neighbours;
	if (!getTile(pCell.x, pCell.z + 2) && !(pCell.z + 2 >= _depth - 1)) neighbours.push_back(coordinate(pCell.x, pCell.z + 2));
	if (!getTile(pCell.x + 2, pCell.z) && !(pCell.x + 2 >= _width - 1)) neighbours.push_back(coordinate(pCell.x + 2, pCell.z));
	if (!getTile(pCell.x - 2, pCell.z) && !(pCell.x - 2 <= 0)) neighbours.push_back(coordinate(pCell.x - 2, pCell.z));
	if (!getTile(pCell.x, pCell.z - 2) && !(pCell.z - 2 <= 0)) neighbours.push_back(coordinate(pCell.x, pCell.z - 2));
	return (neighbours);
}

bool Zone::hasNeighBours(coordinate pCell) {
	if (!getTile(pCell.x, pCell.z + 2) && !(pCell.z + 2 >= _depth - 1)) return true;
	if (!getTile(pCell.x + 2, pCell.z) && !(pCell.x + 2 >= _width - 1)) return true;
	if (!getTile(pCell.x - 2, pCell.z) && !(pCell.x - 2 <= 0)) return true;
	if (!getTile(pCell.x, pCell.z - 2) && !(pCell.z - 2 <= 0)) return true;
	return false;
}

bool Zone::hasCollision(coordinate pPosition) {
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
	printf("\n");
	fclose(fp);
#endif
}

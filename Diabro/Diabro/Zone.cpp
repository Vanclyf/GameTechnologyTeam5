#include "Zone.h"
#include <ctime>
#include <OgreConfigFile.h>
#include <OgreMath.h>

Zone::Zone() {
	
}

Zone::Zone(int pWidth, int pDepth, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries):
_width(pWidth), _depth(pDepth), _maxCityWidth(pMaxCityWidth), _maxCityHeight(pMaxCityHeight)
{	
	if (pWidth % 2 == 0 || pDepth % 2 == 0) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("Zone sizes should be uneven! {W: %d, H: %d} used \n", _width, _depth);
		fclose(fp);
#endif
		//zones use uneven sizes, this ensures walls can be created properly
		_width++;
		_depth++;
	}
	// create an empty grid for dungeon tiles
	_tiles = new int[_width * _depth];
	for (int ix = 0; ix < _width; ++ix) {
		for (int iy = 0; iy < _depth; ++iy) {
			setTile(ix, iy, 0);
		}
	}
	
	generateCities(pMaxTries, pMaxCities);
	int n = generatePathways(cities.size() + 1);
	connectDungeon(cities.size() + 1 + n, 0.5f);

	cleanGrid();
	printGrid();
}

Zone::~Zone()
{

}
/// cleans the grid converting every number either to 1 or 0 based on their current value
void Zone::cleanGrid()
{
	for (int ix = 0; ix < _width; ++ix)
	{
		for (int iz = 0; iz < _depth; ++iz)
		{
			if (getTile(ix, iz) <= 0) setTile(ix, iz, 0); //set all positive values to 1 and negatives to 0
			else setTile(ix, iz, 1);
		}
	}
}

/// checks whether coordinate is within boundaries of the grid
/// \param pCoord coordinate to check
bool Zone::inGrid(Coordinate pCoord) {
	if (pCoord.x >= _width && pCoord.z >= _depth) return false;
	if (pCoord.x < 0 && pCoord.z < 0) return false;
	return true;
}

/// sets a tile to the given value
/// \param pX x coordinate of the tile
/// \param pZ z coordinate of the tile
/// \param pValue value to assign to the given tile 
void Zone::setTile(int pX, int pZ, int pValue) const {
	_tiles[pX + pZ * _width] = pValue;
}

/// sets a tile to the given value
/// \param pCoord coordinate of the tile
/// \param pValue value to assign to the given tile
void Zone::setTile(Coordinate pCoord, int pValue) const {
	_tiles[pCoord.x + pCoord.z * _width] = pValue;
}

/// returns the value of a given tile
/// \param pX x coordinate of the tile
/// \param pZ z coordinate of the tile
int Zone::getTile(int pX, int pZ) const {
	return _tiles[pX + pZ * _width];
}

/// returns the value of a given tile
/// \param pCoord coordinate of the tile
int Zone::getTile(Coordinate pCoord) const {
	return _tiles[pCoord.x + pCoord.z * _width];
}

/// finds an position of a certain value the dungeon
/// \param pMaxId value to look for
/// \param pCheckNeighbours should all eight neighbours have the same value?
Coordinate Zone::getPosition(int pId, bool pCheckNeighbours) {
	std::vector<Coordinate> positions;

	for (int ix = 1; ix < _width - 1; ++ix) {
		for (int iz = 1; iz < _depth - 1; ++iz) {
			if(getTile(ix, iz) == pId) {
				if (pCheckNeighbours) { // check neighbouring cell values
					if( (inGrid(Coordinate(ix - 1, iz - 1)) && getTile(ix - 1, iz - 1) == pId) &&
						(inGrid(Coordinate(ix    , iz - 1)) && getTile(ix    , iz - 1) == pId) &&
						(inGrid(Coordinate(ix + 1, iz - 1)) && getTile(ix + 1, iz - 1) == pId) &&
						(inGrid(Coordinate(ix - 1, iz    )) && getTile(ix - 1, iz    ) == pId) &&
						(inGrid(Coordinate(ix + 1, iz    )) && getTile(ix + 1, iz    ) == pId) &&
						(inGrid(Coordinate(ix - 1, iz + 1)) && getTile(ix - 1, iz + 1) == pId) &&
						(inGrid(Coordinate(ix    , iz + 1)) && getTile(ix    , iz + 1) == pId) &&
						(inGrid(Coordinate(ix + 1, iz + 1)) && getTile(ix + 1, iz + 1) == pId)) {
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
		return positions[iRand]; //return random position
	} else {
		return Coordinate(-1, -1); //return error coordinate
	}
	
}

/// connects rooms and pathways of the dungeon untill all routes are connected
/// \param pMaxId highest value used in the grid
/// \param pChance the decimal percentage of chance a room has to get an extra connection to the dungeon
void Zone::connectDungeon(int pMaxId, float pChance) {

	std::vector<std::pair<Coordinate, int>> connections; ///< holds all possible connections

	for (int i = 0; i < cities.size(); ++i) {

		int rndIndex[2] = { 0,0 };
		int start = connections.size(); // prevents usage of connections of other cities
		int length = getPossibleConnections(cities[i], &connections);

		if (length < 1) continue; //skip cities without connections

		rndIndex[0] = rand() % length + start;
		// set tile to room id value, carving an opening
		setTile(connections[rndIndex[0]].first, connections[rndIndex[0]].second);
		cities[i].connections.push_back(connections[rndIndex[0]].first);
		connections.erase(connections.begin() + rndIndex[0]);
		length--;

		//prevent perfect dungeon by giving each room a chance of opening up another connection
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
	//check if the each room/path is connected to the dungeon
	int regions = changeTileValues(pMaxId);
	
	if (!connections.empty() && regions > 1){
		//find options for connecting a region to the region with the lowest id (marked as id 2)
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

		int regions = changeTileValues(pMaxId);
		
		while (regions > 1 && options.size() > 0) { // opens options until the whole dungeon is connected
			int rnd = rand() % options.size();
			setTile(options[rnd].first, 1);
			cities[options[rnd].second].connections.push_back(options[rnd].first);

			options.erase(options.begin() + rnd);

			// check if dungeon is connected
			regions = changeTileValues(pMaxId);
		}
	}
}

///prints all values used in the grid (Windows only method)
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

/// returns the width and depth of the zone
Coordinate Zone::getResolution() const {
	return(Coordinate(_width, _depth));
}

///checks all tiles and changes the id of connected regions to the lowest id of the two, returns amount of remaining regions
/// \param pMaxIndex maximum index value used in the whole zone
int Zone::changeTileValues(int pMaxIndex) {
	
	int currentRegion = 1;
	int amountOfRegions = 0;
	for (int i = 1; i <= pMaxIndex; ++i) {
		std::vector<Coordinate> positions;
		//pick random cell for current region
		positions.push_back(getPosition(currentRegion, false));
		
		if (inGrid(positions[0])) {
			if (getTile(positions[0]) != currentRegion) { //continue if no options are found for this id
				positions.clear();
				currentRegion++;
				continue;
			}
		}

		if (positions[0].x >= 0 && positions[0].z >= 0) {
			while(!positions.empty()) {
				//find all neighbours (which are >0) and add them to the list
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
				
				//assigns temporary value to cell (negative of id value, one is not used as negative one is used for possible connections)
				setTile(positions[0], -(amountOfRegions + 2));
				positions.erase(positions.begin());
			}
			amountOfRegions++;
		}
		positions.clear();
		currentRegion++;
	}
	for (int ix = 0; ix < _width; ++ix) {
		for (int iz = 0; iz < _depth; ++iz) {
			int n = getTile(ix, iz);
			if (n < 0 && n != -1) {
				// set tiles to correct values
				setTile(ix, iz, getTile(ix, iz) * -1);
			}
		}
	}
	return amountOfRegions;
}

/// finds all possible points to connect a city with a path
/// \param pCity the city for which connections have to be found
/// \param pConnections pointer to connections vector existing of a position and city id
int Zone::getPossibleConnections(City pCity, std::vector<std::pair<Coordinate, int>> *pConnections) {
	int connectionAmount = 0;
	for (int ix = 0; ix < pCity.width; ++ix) {
		for (int iz = 0; iz < pCity.depth; ++iz) {
			//north
			if (getTile(pCity.position.x + ix, pCity.position.z + iz - 1) == 0 && pCity.position.z + iz - 2 > 0) {
				if (getTile(pCity.position.x + ix, pCity.position.z + iz - 2) > 0) {
					//save connection in grid and connection vector
					pConnections->push_back(std::make_pair(Coordinate(pCity.position.x + ix, pCity.position.z + iz - 1), pCity.id));
					setTile(pCity.position.x + ix, pCity.position.z + iz - 1, -1);
					connectionAmount++;
				}
			}
			//east
			if (getTile(pCity.position.x + ix + 1, pCity.position.z + iz) == 0 && pCity.position.x + ix + 2 < _width) {
				if (getTile(pCity.position.x + ix + 2, pCity.position.z + iz) > 0) {
					//save connection in grid and connection vector
					pConnections->push_back(std::make_pair(Coordinate(pCity.position.x + ix + 1, pCity.position.z + iz), pCity.id));
					setTile(pCity.position.x + ix + 1, pCity.position.z + iz, -1);
					connectionAmount++;
				}
			}
			//south
			if (getTile(pCity.position.x + ix, pCity.position.z + iz + 1) == 0 && pCity.position.z + iz + 2 < _depth) {
				if (getTile(pCity.position.x + ix, pCity.position.z + iz + 2) > 0) {
					//save connection in grid and connection vector
					pConnections->push_back(std::make_pair(Coordinate(pCity.position.x + ix, pCity.position.z + iz + 1), pCity.id));
					setTile(pCity.position.x + ix, pCity.position.z + iz + 1, -1);
					connectionAmount++;
				}
			}
			//west
			if (getTile(pCity.position.x + ix - 1, pCity.position.z + iz) == 0 && pCity.position.x + ix - 2 > 0) {
				if (getTile(pCity.position.x + ix - 2, pCity.position.z + iz) > 0) {
					//save connection in grid and connection vector
					pConnections->push_back(std::make_pair(Coordinate(pCity.position.x + ix - 1, pCity.position.z + iz), pCity.id));
					setTile(pCity.position.x + ix - 1, pCity.position.z + iz, -1);
					connectionAmount++;
				}
			}
		}
	}
	return connectionAmount; //returns length of values added to the connection vector
}

/// generates pathways within the generated grid
/// \param pPathId id to start with when generating the path (same as amount of cities)
int Zone::generatePathways(int pPathId) {
	int nIterations = 0;

	while (!checkGrid()) {
		std::vector<Coordinate> cellList;

		//Possible improvement: pass startpos to method to use heuristic for shapes
		//get random empty position
		Coordinate position = getPosition(0, true);
		
		//only use uneven values, paths carve two tiles and only make corners on uneven values
		//even values will cause paths and rooms to collide
		if (position.x % 2 == 0) {
			(position.x + 2 >= _width) ? position.x-- : position.x++;
		}
		if (position.z % 2 == 0) {
			(position.z + 2 >= _depth) ? position.z-- : position.z++;
		}

		cellList.push_back(Coordinate(position.x, position.z));
		int current = 0;
		setTile(cellList[current].x, cellList[current].z, -1); // all currently used cells are marked as -1

		while (!cellList.empty()) { //find each cells neighbours, add them to the list, remove current. Repeat until list is empty
			if (hasNeighBours(cellList[current], 2)) {
				//TODO: select all neighbours at once
				cellList.push_back(getRndNeighbour(cellList[current], pPathId + nIterations));
				++current;
				setTile(cellList[current].x, cellList[current].z, -1);
			}
			else {
				setTile(cellList[current].x, cellList[current].z, pPathId + nIterations);
				cellList.erase(cellList.begin() + current);
				--current;
				//TODO: implement heuristic types for new current cell
			}
		}
		nIterations++; // returns amount of separate paths
	}
	return nIterations;
}

/// finds a random neighbour of pCell
/// \param pCell selected cell
/// \param pPathId id of the drawn path (will be the new id of the cell)
Coordinate Zone::getRndNeighbour(Coordinate pCell, int pPathId) {
	std::vector<Coordinate> neighbours = getNeighbours(pCell);
	int i = rand() % neighbours.size();
	Coordinate difference = neighbours[i];
	
	difference.x = difference.x - pCell.x;
	difference.z = difference.z - pCell.z;

	//mark the cell in between current and next cell as drawn
	if (difference.x == 0) {
		(difference.z > 0) ? setTile(pCell.x, pCell.z + 1, pPathId) : setTile(pCell.x, pCell.z - 1, pPathId);
	}
	else {
		(difference.x > 0) ? setTile(pCell.x + 1, pCell.z, pPathId) : setTile(pCell.x - 1, pCell.z, pPathId);
	}	

	return (Coordinate(neighbours[i]));	
}

/// finds all neighbours of a cell
/// \param pCell selected cell
std::vector<Coordinate> Zone::getNeighbours(Coordinate pCell) {
	std::vector<Coordinate> neighbours;
	if (pCell.z + 2 < _depth && !getTile(pCell.x, pCell.z + 2)) neighbours.push_back(Coordinate(pCell.x, pCell.z + 2));
	if (pCell.x + 2 < _width && !getTile(pCell.x + 2, pCell.z)) neighbours.push_back(Coordinate(pCell.x + 2, pCell.z));
	if (pCell.x - 2 >= 0 && !getTile(pCell.x - 2, pCell.z)) neighbours.push_back(Coordinate(pCell.x - 2, pCell.z));
	if (pCell.z - 2 >= 0 && !getTile(pCell.x, pCell.z - 2)) neighbours.push_back(Coordinate(pCell.x, pCell.z - 2));
	return (neighbours);
}

/// checks whether a cell has neighbours
/// \param pCell selected cell
/// \param pDistance checks for neighbours 'x' cells away, skipping cells in between
bool Zone::hasNeighBours(Coordinate pCell, int pDistance) {
	if (pCell.z + pDistance < _depth - 1 && !getTile(pCell.x, pCell.z + pDistance)) return true;
	if (pCell.x + pDistance < _width - 1 && !getTile(pCell.x + pDistance, pCell.z)) return true;
	if (pCell.x - pDistance >= 0 && !getTile(pCell.x - pDistance, pCell.z)) return true;
	if (pCell.z - pDistance >= 0 && !getTile(pCell.x, pCell.z - pDistance)) return true;
	return false;
}

/// checks whether a position is already taken
/// \param pPosition position to check
bool Zone::hasCollision(Coordinate pPosition) {
	if (inGrid(pPosition))return true;
	return(getTile(pPosition.x, pPosition.z) ? true : false);
}

/// checks wheter a city can be placed on its position
/// \param pC selected city
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

/// checks if all values in the grid are filled (exept for wall positions)
bool Zone::checkGrid() {
	for (int iX = 1; iX < _width; iX += 2) {
		for (int iZ = 1; iZ < _depth; iZ += 2) {
			if (getTile(iX, iZ) == 0) {
				return false;
			}
		}
	}
	return true;
}


/// places a city, if the position has not been taken yet otherwise it returns false
/// \param pC selected city
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


/// generates cities by trying to place them on random positions
/// \param pMaxTries maximum amount of tries before the algorithm quits
/// \param pMaxCities the maximum amount of cities to place
void Zone::generateCities(int pMaxTries, int pMaxCities) {
	int nCities = 0;
	srand(time(NULL));

	for (int iTry = 0; iTry < pMaxTries; ++iTry) {
		//generate width, depth, should be uneven for wall creation
		int width = rand() % (_maxCityWidth - 2) + 2;
		int depth = rand() % (_maxCityHeight - 2) + 2;
		(width % 2 == 0) ? width++ : width;
		(depth % 2 == 0) ? depth++ : depth;

		//generate position, should be uneven for wall creation
		int x = rand() % (_width - width - 1) + 1;
		int z = rand() % (_depth - depth - 1) + 1;
		(x % 2 == 0) ? x++ : x;
		(z % 2 == 0) ? z++ : z;

		//try to place the city
		if (placeCity(City(x, z, width, depth, nCities + 1))) {
			++nCities;
		}
		if (nCities >= pMaxCities) {
			break;
		}
	}
}

/// prints all values of the grid (windows only method)
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

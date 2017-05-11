#ifndef ZONE_H_
#define ZONE_H_

#include "City.h"
#include <vector>

class Zone
{
private:
	int _width;
	int _depth;
	
	int _maxCityWidth;
	int _maxCityHeight;

	int* _tiles; ///< holds the zone grid, filled with all zone positions
	int _numberOfRegions; ///< not yet implemented, decides the amount of closed of regions within the zone

public:
	std::vector<City> cities; ///< vector containing all cities within the zone

	Zone(int pWidth, int pHeight, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries);
	Zone();
	~Zone();

	void setTile(int pX, int pZ, int pValue) const;
	void setTile(Coordinate pCoord, int pValue) const;
	int getTile(int pX, int pZ) const;
	int getTile(Coordinate pCoord) const;
	Coordinate getResolution() const;
	
	Coordinate getPosition(int pId, bool pCheckNeighbours);
	void printGrid();

private:
	void cleanGrid();
	bool inGrid(Coordinate pCoord);

	void connectDungeon(int pId, float pChance);
	int getPossibleConnections(City pCity, std::vector<std::pair<Coordinate, int>> *pConnections);
	int changeTileValues(int pMaxIndex);
	void printValues();
	
	int generatePathways(int pPathId);
	std::vector<Coordinate> getNeighbours(Coordinate pCell);
	Coordinate getRndNeighbour(Coordinate pCell, int nPathId);
	bool hasNeighBours(Coordinate pCell, int pDistance);
	bool checkGrid();
	

	void generateCities(int pMaxTries, int pMaxCities);
	bool hasCollision(Coordinate pPosition);
	bool hasCollision(City pC);
	bool placeCity(City pC);
};

#endif
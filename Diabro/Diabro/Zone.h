#ifndef ZONE_H_
#define ZONE_H_

#include "City.h"
#include <vector>

class Zone
{
private:
	int _width;
	int _depth;
	
	int _numberOfRegions;

	int _maxCityWidth;
	int _maxCityHeight;
	
	//pX + pY * pWidth
	int *_tiles;


public:
	std::vector<City> cities;

	Zone(int pWidth, int pHeight, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries);
	~Zone();

	void setTile(int pX, int pY, int pValue) const;
	void setTile(coordinate pCoord, int pValue) const;
	int getTile(int pX, int pY) const;
	int getTile(coordinate pCoord) const;
	
	void printGrid();

private:
	void connectDungeon(int id, float pChance);
	int getPossibleConnections(City pCity, std::vector<std::pair<coordinate, int>> *pConnections);
	int changeTileValues(int pMaxIndex);
	
	int generatePathways(int pPathId);
	std::vector<coordinate> getNeighbours(coordinate pCell);
	coordinate getRndNeighbour(coordinate pCell, int nPathId);
	bool hasNeighBours(coordinate pCell);
	bool checkGrid();
	coordinate getPosition(int pId, bool pCheckNeighbours);

	void generateCities(int pMaxTries, int pMaxCities);
	bool hasCollision(coordinate pPosition);
	bool hasCollision(City pC);
	bool placeCity(City pC);
};

#endif
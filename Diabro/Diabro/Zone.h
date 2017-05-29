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
	Zone();
	~Zone();

	void setTile(int pX, int pY, int pValue) const;
	void setTile(Coordinate pCoord, int pValue) const;
	int getTile(int pX, int pY) const;
	int getTile(Coordinate pCoord) const;
	Coordinate getResolution() const;
	
	void printGrid();

private:
	void cleanGrid();

	void connectDungeon(int id, float pChance);
	int getPossibleConnections(City pCity, std::vector<std::pair<Coordinate, int>> *pConnections);
	int changeTileValues(int pMaxIndex);
	void printValues();
	
	int generatePathways(int pPathId);
	std::vector<Coordinate> getNeighbours(Coordinate pCell);
	Coordinate getRndNeighbour(Coordinate pCell, int nPathId);
	bool hasNeighBours(Coordinate pCell);
	bool checkGrid();
	Coordinate getPosition(int pId, bool pCheckNeighbours);

	void generateCities(int pMaxTries, int pMaxCities);
	bool hasCollision(Coordinate pPosition);
	bool hasCollision(City pC);
	bool placeCity(City pC);
};

#endif
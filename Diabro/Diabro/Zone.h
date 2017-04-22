#ifndef ZONE_H_
#define ZONE_H_

#include "City.h"
#include <vector>

class Zone
{
private:
	int _width;
	int _depth;
	
	int _maxTries;
	int _maxCities;
	
	int _numberOfRegions;

	int _maxCityWidth;
	int _maxCityHeight;
	
	//pX + pY * pWidth
	int *_tiles;
public:
	std::vector<City> cities;

	Zone(int pWidth, int pHeight, int pMaxCityWidth, int pMaxCityHeight, int pMaxCities, int pMaxTries);
	~Zone();

	void setTile(int x, int y, int value) const;
	int getTile(int x, int y) const;
	bool hasCollision(City c);

	void printGrid();

private:
	void GenerateCities(int pMaxTries, int pMaxCities);
	bool PlaceCity(int pX, int pZ, int pWidth, int pDepth, int pCityId);
};

#endif
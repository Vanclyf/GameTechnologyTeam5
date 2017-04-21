#ifndef ZONE_H_
#define ZONE_H_

#include "City.h"
#include <vector>

class Zone
{
	int _width;
	int _depth;
	
	int _maxTries;
	int _maxCities;
	
	int _NumberOfRegions;

	int _MaxCityWidth;
	int _MaxCityHeight;
	
	//x + y * width
	int *_tiles;

	
public:
	std::vector<City> cities;

	Zone(int width, int height, int maxCityWidth, int maxCityHeight, int maxCities, int maxTries);
	~Zone();

	void setTile(int x, int y, int value) const;
	int getTile(int x, int y) const;
	bool hasCollision(City c);

	void printGrid();

private:
	void GenerateCities(int maxTries, int maxCities);
	bool PlaceCity(int x, int y, int width, int height, int roomId);
};

#endif
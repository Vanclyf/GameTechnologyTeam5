#ifndef CITY_H_
#define CITY_H_
#include <vector>

struct Coordinate {
	int x;
	int z;
	Coordinate(int x, int z) : x(x), z(z) {	}
};

enum RoomType
{
	EmptyRT,
	CityRT,
	HideoutRT,
	HubRT,
	sizeRT
};

class City
{
public:
	Coordinate position;
	RoomType typeFlag;
	int width;
	int depth;
	int id;

	std::vector<Coordinate> connections;

	City(int pX, int pZ, int pWidth, int pDepth, int pId);
	~City();

private:
	void setRndType();

};

#endif
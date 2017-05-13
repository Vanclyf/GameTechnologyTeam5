#ifndef CITY_H_
#define CITY_H_
#include <vector>

/// integer coordinate representing a 2D position
struct Coordinate {
	int x;
	int z;
	Coordinate(int pX, int pZ) : x(pX), z(pZ) {	}
};

///different types of rooms
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
	Coordinate position; ///< upper left corner position of room
	RoomType typeFlag;
	int width;
	int depth;
	int id; ///< unique id

	//TODO: make local position
	std::vector<Coordinate> connections; ///< all doorway positions in grid coordinates 

	City(int pX, int pZ, int pWidth, int pDepth, int pId);
	~City();

	Coordinate getCenterTile();
	Coordinate getRandomTile();
private:
	void setRndType();

};

#endif
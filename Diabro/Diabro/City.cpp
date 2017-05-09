#include "City.h"
#include <stdlib.h>

City::City(int pX, int pZ, int pWidth, int pDepth, int pId) :
position(Coordinate(pX, pZ)), width(pWidth), depth(pDepth), id(pId)
{
	setRndType();
}

City::~City()
{
}

Coordinate City::getCenterTile() {
	int x = ceil(position.x + width / 2.0f);
	int z = ceil(position.z + depth / 2.0f);
	return Coordinate(x, z);
}

Coordinate City::getRandomTile() {
	int x = rand() % width;
	int z = rand() % depth;
	return Coordinate(position.x + x, position.z + z);
}


void City::setRndType()
{
	//TODO:improve picking method
	srand(355 * id);
	typeFlag = static_cast<RoomType> (rand() % static_cast<int>(RoomType::sizeRT));
}


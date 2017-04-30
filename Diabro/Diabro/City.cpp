#include "City.h"

City::City(int pX, int pZ, int pWidth, int pDepth, int pId) :
position(coordinate(pX, pZ)), width(pWidth), depth(pDepth), id(pId)
{
}

City::~City()
{
}

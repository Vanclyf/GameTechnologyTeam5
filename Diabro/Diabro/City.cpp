#include "City.h"
#include <cstdio>

City::City(int x, int y, int width, int height, int id) :
_x(x), _y(y), _width(width), _height(height), _id(id)
{
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("city %d created \n", id);
	fclose(fp);
}

City::~City()
{
}

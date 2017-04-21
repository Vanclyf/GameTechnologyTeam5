#include "City.h"
#include <cstdio>

City::City(int x, int z, int width, int depth, int id) :
_x(x), _z(z), _width(width), _depth(depth), _id(id)
{
	/*FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("city %d created \n", id);
	fclose(fp);*/
}

City::~City()
{
}

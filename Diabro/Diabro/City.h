#ifndef CITY_H_
#define CITY_H_
#include <vector>

struct connection {
	int x;
	int y;
};

class City
{
public:
	int x;
	int z;
	int width;
	int depth;
	int id;

	std::vector<connection> connections;

	City(int pX, int pY, int pWidth, int pHeight, int pId);
	~City();
};

#endif
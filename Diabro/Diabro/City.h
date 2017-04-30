#ifndef CITY_H_
#define CITY_H_
#include <vector>

struct coordinate {
	int x;
	int z;
	coordinate(int x, int z) : x(x), z(z) {	}
};

class City
{
public:
	coordinate position;
	int width;
	int depth;
	int id;

	std::vector<coordinate> connections;

	City(int pX, int pZ, int pWidth, int pDepth, int pId);
	~City();

};

#endif
#ifndef CITY_H_
#define CITY_H_

class City
{
public:
	int _x;
	int _z;
	int _width;
	int _depth;
	int _id;

	City(int x, int y, int width, int height, int id);
	~City();
};

#endif
#ifndef CITY_H_
#define CITY_H_

class City
{
public:
	int x;
	int z;
	int width;
	int depth;
	int id;

	City(int pX, int pY, int pWidth, int pHeight, int pId);
	~City();
};

#endif
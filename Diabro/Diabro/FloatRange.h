#ifndef FLOAT_RANGE_H_
#define FLOAT_RANGE_H_

#pragma once
#include <iostream>

class FloatRange
{
public:
	FloatRange(float min, float max);
	~FloatRange();

	int GetMin()
	{
		return _min;
	}

	int GetMax()
	{
		return _max;
	}

	int RandomInRange();

private:
	int _min;
	int _max;
};

#endif
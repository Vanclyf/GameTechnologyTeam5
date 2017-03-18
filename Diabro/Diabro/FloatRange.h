#ifndef FLOAT_RANGE_H_
#define FLOAT_RANGE_H_

#pragma once

class FloatRange
{
public:
	FloatRange(float, float);
	~FloatRange();

	int getMin() { return _min; }

	int getMax() { return _max; }

	int randomInRange();

private:
	int _min;
	int _max;
};

#endif
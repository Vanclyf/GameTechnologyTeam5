#include "FloatRange.h"
#include <iostream>


FloatRange::FloatRange(float min, float max)
{
	this->_min = min;
	this->_max = max;
}


FloatRange::~FloatRange()
{
}


/// <summary>
/// Returns an Random Number between the set Min and Max.
/// </summary>
/// <returns></returns>
int FloatRange::RandomInRange()
{
	return rand() % GetMax() + GetMin();
}



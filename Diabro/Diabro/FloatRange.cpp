#include "FloatRange.h"

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
FloatRange::FloatRange(float min, float max)
{
	this->_min = min;
	this->_max = max;
}


/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
FloatRange::~FloatRange()
{
}


/// <summary>
/// Returns an random number between the min and max.
/// </summary>
/// <returns>Random integer in range</returns>
int FloatRange::RandomInRange()
{
	return rand() % GetMax() + GetMin();
}



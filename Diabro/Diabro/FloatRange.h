#pragma once
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


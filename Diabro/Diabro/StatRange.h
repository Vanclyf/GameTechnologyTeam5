#pragma once
#include <stddef.h>
#include "CharacterStats.h"
#include "FloatRange.h"

using namespace std;

class StatRange
{
public:
	vector<StatType> GetStatTypes()
	{
		return _statTypes;
	}

	FloatRange GetFloatRange()
	{
		return _range;
	}

private:
	vector<StatType> _statTypes;
	FloatRange _range;
};

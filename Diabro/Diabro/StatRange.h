#ifndef STAT_RANGE_H_
#define STAT_RANGE_H_

#pragma once
#include <stddef.h>
#include "CharacterStats.h"
#include "FloatRange.h"

using namespace std;

class StatRange
{
public:
	vector<StatType> getStatTypes() { return _statTypes; }
	FloatRange getFloatRange() { return _range; }

private:
	vector<StatType> _statTypes;
	FloatRange _range;
};

#endif
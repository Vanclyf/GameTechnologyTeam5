#ifndef STAT_RANGE_H_
#define STAT_RANGE_H_

#pragma once
#include "CharacterStats.h"
#include "FloatRange.h"

class StatRange
{
public:
	std::vector<StatType> getStatTypes() { return _statTypes; }
	FloatRange getFloatRange() { return _range; }

private:
	std::vector<StatType> _statTypes;
	FloatRange _range;
};

#endif
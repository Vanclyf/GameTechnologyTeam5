#ifndef STAT_RANGE_H_
#define STAT_RANGE_H_

#pragma once
#include "CharacterStats.h"
#include "FloatRange.h"

class StatRange
{
public:
	StatRange(StatType pStatType, FloatRange pFloatRange) : _statType(pStatType), _range(pFloatRange){}
	StatType getStatType() { return _statType; }
	FloatRange getFloatRange() { return _range; }

private:
	StatType _statType;
	FloatRange _range;
};

#endif
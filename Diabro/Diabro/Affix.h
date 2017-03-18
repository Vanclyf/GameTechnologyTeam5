#ifndef AFFIX_H_
#define AFFIX_H_

#pragma once
#include <string>
#include "Modifier.h"

class Affix
{
public:

	int getId()
	{
		return _id;
	}

	std::string getName()
	{
		return _name;
	}

	int getTier()
	{
		return _tier;
	}

	float getValue()
	{
		return _value;
	}

	bool isPresent()
	{
		return _isPresent;
	}

	Modifier getModifier()
	{
		return _modifier;
	}

private:
	int _id;
	std::string _name;
	int _tier;
	Modifier _modifier;
	float _value;
	bool _isPresent;

};

#endif

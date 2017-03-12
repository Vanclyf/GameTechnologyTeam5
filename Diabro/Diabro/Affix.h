#pragma once
#include <string>
#include <rpcndr.h>
#include "Modifier.h"

using namespace std;

class Affix
{
public:

	int GetId()
	{
		return _id;
	}

	string GetName()
	{
		return _name;
	}

	int GetTier()
	{
		return _tier;
	}

	float GetValue()
	{
		return _value;
	}

	bool isPresent()
	{
		return _isPresent;
	}

	Modifier GetModifier()
	{
		return _modifier;
	}
private:
	int _id;
	string _name;
	int _tier;
	Modifier _modifier;
	float _value;
	bool _isPresent;



};


#pragma once
#ifndef	BUILDING_TYPE_H_
#define BUILDING_TYPE_H_
#include <vector>
#include <OgreSceneNode.h>
#include "City.h"


class BuildingType: public City
{
public:
	int buildingTypeId;
	
	BuildingType(int buildingTypeId);

	~BuildingType();

protected:
	

private:


};
#endif

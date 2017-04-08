#ifndef CITY_MANAGER_H_


#pragma once
#include "LevelManager.h"


class CityManager : public LevelManager
{
public:
	CityManager();
	void init(); // initilializes everything, also kevin is dope
	void generateCity(int, int, int); //Will generate city based on position and numberofbuildings
	int parentIteration;
	int childIteration;


protected:
	std::vector<Ogre::SceneNode*> CityManager::nodeIteration(Ogre::SceneNode *); //simple method that will iterate through all child nodes and set them in an array to eb used. (maybe for a "BaseController)
	bool checkCollision(Ogre::SceneNode *); //Checks if buildings are colliding with one another
	bool checkEntryWay(Ogre::SceneNode *); //Checks if the buildings are blocking entryways
	int assignBuildingRole(Ogre::SceneNode *); //Assign roles to buildings in the city
private:
	std::vector <Ogre::SceneNode*> buildings;
	Ogre::SceneManager *manager;
	Ogre::SceneNode* _cityNode;
	Ogre::Entity* _signEntity;
	Ogre::SceneNode* _rootNode;
	Ogre::SceneNode* _roleNode;
	int _numberOfBuildings;
	int role;

};
#endif#pragma once

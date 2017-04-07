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
	std::vector<Ogre::SceneNode*> CityManager::nodeIteration(Ogre::SceneNode *);
	bool checkCollision(Ogre::SceneNode *, int); //Checks if buildings are colliding with one another
	bool checkEntryWay(Ogre::SceneNode *, int); //Checks if the buildings are blocking entryways
	int assignBuildingRole(Ogre::SceneNode *, int);
private:
	std::vector <Ogre::SceneNode*> detachable;
	Ogre::SceneManager *manager;
	Ogre::SceneNode* _cityNode;
	Ogre::Entity* _signEntity;
	Ogre::SceneNode* _rootNode;
	Ogre::SceneNode* _buildings;
	Ogre::SceneNode* _roleNode;
	int _numberOfBuildings;
	int role;

};
#endif#pragma once

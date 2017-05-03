#include "City.h"
#include <stdlib.h>
#include "GameManager.h"

City::City(int pX, int pZ, int pWidth, int pDepth, int pId, int pScalar) :
position(Coordinate(pX, pZ)), width(pWidth), depth(pDepth), id(pId), scalar(pScalar)
{
	setRndType();

}

void City::init()
{
	generateBuildings(id, position.x, position.z, width, depth);
}

City::~City()
{
}

void City::setRndType()
{
	//TODO:improve picking method
	srand(355 * id);
	typeFlag = static_cast<RoomType> (rand() % static_cast<int>(RoomType::sizeRT));
}

void City::generateBuildings(int id, int x, int z, int width, int depth)
{
	_rootNode = GameManager::getSingletonPtr()->getSceneManager()->getRootSceneNode();
	manager = GameManager::getSingletonPtr()->getSceneManager();
		
	for (int i = 0; i < std::rand() % 10 + 1; i++)
	{
		printf(" buildingsnumber: %d \n", i);
		std::stringstream nodename("citybuildingNode");
		//TODO: make it an ID
		Ogre::SceneNode* buildingNode = _rootNode->createChildSceneNode();
		Ogre::Entity* _buildingEntity = manager->createEntity("cube.mesh");

		buildingNode->setPosition(Ogre::Vector3(0, 0, 0));
		buildingNode->attachObject(_buildingEntity);
		//TODO: Change the numbers here to match those provided by levelgen CHECK
		int xPos = GameManager::getSingletonPtr()->getRandomInRange(x, width - 1);
		int zPos = GameManager::getSingletonPtr()->getRandomInRange(z, depth - 1);
		buildingNode->setPosition(xPos * 1000, 50, zPos * 1000);//GameManager::getSingletonPtr()->getRandomInRange(x * 1000, (x + width) * 1000), 50, GameManager::getSingletonPtr()->getRandomInRange(z * 1000, (z + depth) * 1000));

		nodeList(buildingNode);
		assignBuildingRole(buildings);	
	}
}


int City::assignBuildingRole(std::vector<Ogre::SceneNode *>  buildings)
{
	std::stringstream nodename("buildingRoleNode");
	
	for (int i = 0; i < buildings.size(); i++) {

		//nodename << childIteration << "_" << parentIteration << "_" << i;
		int roles = rand() % 6;

		switch (roles) // assign building random professions by giving them a rolenode
		{

		case 0:
			_roleNode = (Ogre::SceneNode *)buildings[i]->createChild();
			_signEntity = manager->createEntity("Barrel.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 1:
			_roleNode = (Ogre::SceneNode *)buildings[i]->createChild();
			_signEntity = manager->createEntity("Barrel.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 2:
			_roleNode = (Ogre::SceneNode *)buildings[i]->createChild();
			_signEntity = manager->createEntity("Knot.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 3:
			_roleNode = (Ogre::SceneNode *)buildings[i]->createChild();
			_signEntity = manager->createEntity("Barrel.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 4:
			_roleNode = (Ogre::SceneNode *)buildings[i]->createChild();
			_signEntity = manager->createEntity("Athene.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 5:
			break;
		}
		//printf("%d", roles);
	}

	return role;
}


std::vector<Ogre::SceneNode*> City::nodeList(Ogre::SceneNode* pBuildingNode)
{
	buildings.push_back(pBuildingNode);
	return buildings;

}

/**std::vector<Ogre::SceneNode*> City::nodeIteration(Ogre::SceneNode *pNodeName)
{
	Ogre::SceneNode::ChildNodeIterator cNode = pNodeName->getChildIterator();
	while (cNode.hasMoreElements()) {
		buildings.push_back((Ogre::SceneNode *)cNode.getNext());
	}
	return buildings;
}**/


int City::getScaladWidth(int width, int scalar)
{
	return width*scalar;
}

int City::getScaladDepth(int depth, int scalar)
{
	return depth*scalar;
}
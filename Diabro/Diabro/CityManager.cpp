#include "CityManager.h"
#include "GameManager.h"

CityManager::CityManager() 
{
	
}
//TODO: For random positions have the location of the cities
void CityManager::init()
{
	 manager = GameManager::getSingletonPtr()->getSceneManager();
	_rootNode = GameManager::getSingletonPtr()->getSceneManager()->getRootSceneNode();
	for (int i = 0; i < 3; i++)
	{
		parentIteration = i;
		std::srand(i);
		

		_cityNode = _rootNode->createChildSceneNode("cityNode " + parentIteration);
		generateCity(std::rand() % 10000 + 10, std::rand() % 10000 + 10, std::rand() % 11 +1);
	}
			
		
	
}

void CityManager::generateCity(int sizeX, int sizeZ, int _numberOfBuildings)
{
	
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	
	printf(" number of buildings: %d \n", _numberOfBuildings);
	printf(" location of X: %d  location of Z: %d \n", sizeX, sizeZ);
	for (int i = 0; i < _numberOfBuildings; i++)
	{
		childIteration = i;
		printf(" parent  %d and child %d \n", parentIteration, childIteration);
		
		std::stringstream nodename("citybuildingNode");
		// builds a string stream around the string literal
		nodename << childIteration << "_" << parentIteration;
		// writes the numbers into the stream the same way `cin << number;` would
		// turning the number into a string for you
		Ogre::SceneNode* buildingNode = _cityNode->createChildSceneNode(nodename.str());
		
		Ogre::Entity* _buildingEntity = manager->createEntity("cube.mesh");
		
		buildingNode->attachObject(_buildingEntity);
		//TODO: Change the numbers here to match those provided by levelgen 
		buildingNode->setPosition(rand() % (sizeX +500) + sizeX, 50, rand() % (sizeZ +500) + sizeZ); 
		buildingNode->setScale(rand() % 6+1 , rand() % 6 + 1, rand() % 6 + 1);
			
		Ogre::Vector3 buildingpos = buildingNode->getPosition();
		Ogre::Vector3 buildingscale = buildingNode->getScale();
				
		printf("positions of building nodes %f, %f, %f " , buildingpos.x, buildingpos.y, buildingpos.z);
		printf("scale of building nodes %f, %f, %f \n", buildingscale.x, buildingscale.y, buildingscale.z);	
	}
	//reposition and roleassignement if needed
	checkCollision(_cityNode, _numberOfBuildings);
	checkEntryWay(_cityNode, _numberOfBuildings);
	//assignBuildingRole(_cityNode, _numberOfBuildings);
	fclose(fp);
#endif
}
//TODO: check if buildings are colliding needs collison implemented
bool CityManager::checkCollision(Ogre::SceneNode *_cityNode, int _numberOfBuildings)
{
	for (int i = 0; i < _numberOfBuildings; i++)
	{
		//Ogre::Node *buildingNode =_cityNode->getChild("buildingNode");
		
		
	}
	
	return true;
	
}
//TODO: check if entryways aren't being blocked needs entryways 
bool CityManager::checkEntryWay(Ogre::SceneNode *_cityNode, int _numberOfBuildings)
{
	for (int i = 0; i < _numberOfBuildings; i++)
	{
		//Ogre::Child *buildingNode = _cityNode->getChildIterator();

	}

	return true;
}

//Source: http://www.ogre3d.org/forums/viewtopic.php?f=2&t=77945 by Kojack
int CityManager::assignBuildingRole(Ogre::SceneNode * _cityNode, int _numberOfBuildings)
{
	std::stringstream nodename("buildingRoleNode");
	Ogre::SceneNode::ChildNodeIterator cNode = _cityNode->getChildIterator();
	std::vector <Ogre::SceneNode*> detachable;
	while (cNode.hasMoreElements()) {
		detachable.push_back((Ogre::SceneNode *)cNode.getNext());
	}
		for (int i = 0; i < detachable.size(); i++) {
			nodename << childIteration << "_" << parentIteration << "_" << i;
			switch (rand() % 5) // assign building random proffessions by giving them a rolenode
			{
			case 0:
				_roleNode = ( Ogre::SceneNode *)cNode.getNext()->createChild(nodename.str());
				_signEntity = manager->createEntity("Barrel.mesh");
				_roleNode->attachObject(_signEntity);
				break;
			case 1:
				_roleNode = (Ogre::SceneNode *)cNode.getNext()->createChild(nodename.str());
				_signEntity = manager->createEntity("Barrel.mesh");
				_roleNode->attachObject(_signEntity);
				break;
			case 2:
				_roleNode = (Ogre::SceneNode *)cNode.getNext()->createChild(nodename.str());
				_signEntity = manager->createEntity("Barrel.mesh");
				_roleNode->attachObject(_signEntity);
				break;
			case 3:
				_roleNode = (Ogre::SceneNode *)cNode.getNext()->createChild(nodename.str());
				_signEntity = manager->createEntity("Barrel.mesh");
				_roleNode->attachObject(_signEntity);
				break;
			case 4:
				_roleNode = (Ogre::SceneNode *)cNode.getNext()->createChild(nodename.str());
				_signEntity = manager->createEntity("Barrel.mesh");
				_roleNode->attachObject(_signEntity);
				break;
			default:
				break;
			}
		}
	
	return role;
}



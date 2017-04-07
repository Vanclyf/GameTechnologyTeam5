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
	for (int i = 0; i < 1; i++)
	{
		parentIteration = i;
		std::srand(5);
		

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
	assignBuildingRole(_cityNode, _numberOfBuildings);
	fclose(fp);
#endif
}
//TODO: check if buildings are colliding needs collison implemented
bool CityManager::checkCollision(Ogre::SceneNode *_cityNode, int _numberOfBuildings)
{
//TODO: check with other node   	
	Ogre::SceneNode * previousNode; 
	Ogre::SceneNode::ChildNodeIterator cNode = _cityNode->getChildIterator();
	while (cNode.hasMoreElements()) {

		detachable.push_back((Ogre::SceneNode *)cNode.getNext());
	}
	for (int i=0; i < detachable.size(); i++)
	{
		//Ogre::Node *buildingNode =_cityNode->getChild("buildingNode");
		
		
	}
	
	return true;
	
}
//TODO: check if entryways aren't being blocked needs entryways 
bool CityManager::checkEntryWay(Ogre::SceneNode *_cityNode, int _numberOfBuildings)
{
	nodeIteration(_cityNode);
	Ogre::Vector3 entryway =  Ogre::Vector3(5000, 0, 2800);
	for (int i = 0; i < detachable.size(); i++)
	{
		while (detachable[i]->getPosition().distance(entryway) < 150) //TODO: compare with entryway positions
		{
			detachable[i]->setPosition(detachable[i]->getPosition().x -10,0, detachable[i]->getPosition().z);
		}

	}

	return true;
}


//Source: http://www.ogre3d.org/forums/viewtopic.php?f=2&t=77945 by Kojack
int CityManager::assignBuildingRole(Ogre::SceneNode * _cityNode, int _numberOfBuildings)
{
	std::stringstream nodename("buildingRoleNode");
	nodeIteration(_cityNode);
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	
	for (int i = 0; i < detachable.size(); i++) {
		
		nodename << childIteration << "_" << parentIteration << "_" << i;
		int roles = rand() % 5;
	
		switch (roles) // assign building random professions by giving them a rolenode
		{
			
		case 0:
			_roleNode = ( Ogre::SceneNode *)detachable[i]->createChild(nodename.str());
			_signEntity = manager->createEntity("Barrel.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 1:
			_roleNode = (Ogre::SceneNode *)detachable[i]->createChild(nodename.str());
			_signEntity = manager->createEntity("Barrel.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 2:
			_roleNode = (Ogre::SceneNode *)detachable[i]->createChild(nodename.str());
			_signEntity = manager->createEntity("Knot.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 3:
			_roleNode = (Ogre::SceneNode *)detachable[i]->createChild(nodename.str());
			_signEntity = manager->createEntity("Barrel.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		case 4:
			_roleNode = (Ogre::SceneNode *)detachable[i]->createChild(nodename.str());
			_signEntity = manager->createEntity("Athene.mesh");
			_roleNode->attachObject(_signEntity);
			_roleNode->setPosition(0, 100, 0);
			break;
		default:
			break;
		}
		printf("%d", roles);
	}
	fclose(fp);
	return role;
}

//will create a array of childNodes can be relatively widely copied
std::vector<Ogre::SceneNode*> CityManager::nodeIteration(Ogre::SceneNode *pNodeName)
{
	Ogre::SceneNode::ChildNodeIterator cNode = pNodeName->getChildIterator();
	while (cNode.hasMoreElements()) {
		detachable.push_back((Ogre::SceneNode *)cNode.getNext());
	}
	return detachable;
}



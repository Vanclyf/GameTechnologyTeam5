#ifndef CITY_H_
#define CITY_H_
#include <vector>
#include <OgreSceneNode.h>

struct connection {
	int x;
	int y;
};

class City
{
public:
	int x;
	int z;
	int width;
	int depth;
	int id;
	int scalar;
	void init();
	City(int pX, int pZ, int pWidth, int pHeight, int pId, int scalar);
	
	~City();

protected:
	std::vector<Ogre::SceneNode*> City::nodeIteration(Ogre::SceneNode *); //simple method that will iterate through all child nodes and set them in an array to eb used. (maybe for a "BaseController)
	bool checkCollision(Ogre::SceneNode *); //Checks if buildings are colliding with one another
	bool checkEntryWay(Ogre::SceneNode *); //Checks if the buildings are blocking entryways
	int assignBuildingRole(std::vector<Ogre::SceneNode*> ); //Assign roles to buildings in the city
	int getScaladWidth(int width, int scalar);
	int getScaladDepth(int depth, int scalar);
	std::vector<Ogre::SceneNode*>City::nodeList(Ogre::SceneNode* pBuildingNode);
	
private:
	
	int buildingId;
	int parentIteration;
	int childIteration;
	std::vector<connection> connections;
	void generateBuildings(int id, int x, int z, int width, int depth);
	int _scaledWidth;
	int _scaledDepth;
	int *_tiles2;
	std::vector <Ogre::SceneNode*> buildings;
	Ogre::SceneManager *manager;
	Ogre::Entity* _signEntity;
	Ogre::SceneNode* _rootNode;
	Ogre::SceneNode* _roleNode;
	int _numberOfBuildings;
	int role;
};
#endif
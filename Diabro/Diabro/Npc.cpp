#include "Npc.h"

Npc::Npc(Ogre::SceneNode* myNode, Ogre::Entity* myEntity) : BaseNpc(myNode, myEntity), _inDialog(false)
{

}

void Npc::update(Ogre::Real deltatime)
{
	BaseNpc::update(deltatime);

	if(_inDialog)
	{
		//TODO: it's not movement that should be changed, since it should become a const var
		_movespeed = 0;
	} else
	{
		_movespeed = 100;
	}
}


bool Npc::dialog(Ogre::Vector3 playerPos)
{	
	_inDialog = true;

	Ogre::Real distance = _myNode->getPosition().distance(playerPos);

	if (distance < 200) // needs to be tweaked
	{
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("dialog on");
		fclose(fp);		
		
		return true;
	} else
	{	
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("out of range for dialog");
		fclose(fp);	
		
		return false;
	}
}











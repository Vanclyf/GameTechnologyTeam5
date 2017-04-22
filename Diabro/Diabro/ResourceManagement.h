/*
-----------------------------------------------------------------------------
Filename:    ResourceManagement.h
-----------------------------------------------------------------------------
*/

#ifndef RESOURCEMANAGEMENT_H_
#define RESOURCEMANAGEMENT_H_

#include "BaseApplication.h"
#include "LevelManager.h"
#include <OgreSingleton.h>


//---------------------------------------------------------------------------

class ResourceManagement : public BaseApplication, public Ogre::Singleton<ResourceManagement>
{
public:
	ResourceManagement(void);
	~ResourceManagement(void);
	 void createResource(std::string, std::string, std::string, std::string);
	 void unloadResource(std::string);
	 void loadResource(std::string);
	 void unloadResourceGoup(std::string);
	 void reloadResource(std::string);

	




protected:
	 
	
private:
	std::string pLocation;
	Ogre::Resource* resource;
	Ogre::ResourceGroupManager* manager = new Ogre::ResourceGroupManager;
	
};

//---------------------------------------------------------------------------

#endif // #ifndef __ResourceManagement_h_

//---------------------------------------------------------------------------
#pragma once

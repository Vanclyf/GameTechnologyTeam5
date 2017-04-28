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

class ResourceManagement 
{
public:
	ResourceManagement();
	~ResourceManagement();
	
	void  initialize();
	void createResource(std::string, std::string, std::string, std::string, std::string);
	void unloadResource(std::string, std::string);
	void loadResource(std::string);
	void unloadResourceGoup(std::string);
	void reloadResource(std::string, std::string);
	void createGroup(std::string);
	void createRoot();

	




protected:
	//ResourceManagement* rManager;
	
private:
	Ogre::Resource* _resource;
	Ogre::ResourceManager* _resourceMgr;
	Ogre::ResourceGroupManager* _groupManager ;
	
};

//---------------------------------------------------------------------------

#endif // #ifndef __ResourceManagement_h_

//---------------------------------------------------------------------------
#pragma once

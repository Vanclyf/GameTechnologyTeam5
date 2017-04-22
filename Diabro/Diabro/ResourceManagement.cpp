/*
-----------------------------------------------------------------------------
Filename:    ResourceManagement.cpp
-----------------------------------------------------------------------------
 
*/
#include "ResourceManagement.h"

/* A list with the current resourcetypes that are supported by Ogre more can be added 
 *	texture
 *	skeleton
 *	material
 *	mesh
 *	font
 *	highlevelgpuprogram
 *	gpuprogram
 *
 *
 *
 *
 */

void ResourceManagement::createResource(std::string pLocation, std::string pResourceName, std::string pResourceType, std::string pGroupName)
{
	manager->getSingleton().addResourceLocation(pLocation , "Mesh");
	manager->getSingleton().declareResource(pResourceName, pResourceType, pGroupName);
	manager->getSingleton().initialiseResourceGroup(pGroupName);
	// Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); can be used to just load all, need decision which we want
}

void ResourceManagement::unloadResource(std::string pResourceName) // unloads a single resource
{
	resource->unload();	
}

void ResourceManagement::unloadResourceGoup(std::string pGroupName)
{
	manager->getSingleton().unloadResourceGroup(pGroupName);
}

void ResourceManagement::loadResource(std::string pGroupName)
{
	manager->getSingleton().loadResourceGroup(pGroupName);
}

void ResourceManagement::reloadResource(std::string pResourceName )
{
	resource->reload();
	
}
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

 /// <summary>
 /// Creates the resource.
 /// reference material go here http://www.ogre3d.org/tikiwiki/Resources+and+ResourceManagers 
 /// </summary>
 /// <param name="pLocation">The p location.</param>
 /// <param name="pResourceName">Name of the p resource.</param>
 /// <param name="pResourceType">Type of the p resource.</param>
 /// <param name="pGroupName">Name of the p group.</param>
void ResourceManagement::createResource(std::string pLocation, std::string pLocType, std::string pResourceName, std::string pResourceType, std::string pGroupName)
{
	_groupManager->getSingleton().addResourceLocation(pLocation , pLocType);
	_groupManager->getSingleton().declareResource(pResourceName, pResourceType, pGroupName);
	_groupManager->getSingleton().initialiseResourceGroup(pGroupName);
	// Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); can be used to just load all, need decision which we want
}

/// <summary>
/// Unloads the resource.
/// </summary>
/// <param name="pResourceName">Name of the p resource.</param>
/// <param name="pGroupName">Name of the p group.</param>
void ResourceManagement::unloadResource(std::string pResourceName, std::string pGroupName) // unloads a single resource
{
	Ogre::ResourcePtr ptr = _resourceMgr->getResourceByName(pResourceName);
	ptr->unload();
	_resourceMgr->remove(pResourceName);	
}

/// <summary>
/// Unloads the resource goup.
/// </summary>
/// <param name="pGroupName">Name of the p group.</param>
void ResourceManagement::unloadResourceGoup(std::string pGroupName)
{
	_groupManager->getSingleton().unloadResourceGroup(pGroupName);
	
}

/// <summary>
/// Loads the resource.
/// </summary>
/// <param name="pGroupName">Name of the p group.</param>
void ResourceManagement::loadResource(std::string pGroupName)
{
	_groupManager->getSingleton().loadResourceGroup(pGroupName);
}

/// <summary>
/// Reloads the resource.
/// </summary>
/// <param name="pResourceName">Name of the p resource.</param>
/// <param name="pGroupName">Name of the p group.</param>
void ResourceManagement::reloadResource(std::string pResourceName, std::string pGroupName)
{
	Ogre::ResourcePtr ptr = _resourceMgr->load(pResourceName, pGroupName);
	ptr->escalateLoading();
	ptr->reload();
	
}
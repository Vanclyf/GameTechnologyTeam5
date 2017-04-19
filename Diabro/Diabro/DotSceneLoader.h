/// ------------------------------------
/// DOTSCENE LOADER: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=New+DotSceneLoader+header
/// ------------------------------------

#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H

#pragma once

// Includes
#include <Ogre/OgreString.h>
#include <Ogre/OgreVector3.h>
#include <Ogre/OgreQuaternion.h>
#include <vector>
#include "tinyxml2.h"

class nodeProperty {
public:
	Ogre::String nodeName;
	Ogre::String propertyNm;
	Ogre::String valueName;
	Ogre::String typeName;

	nodeProperty(const Ogre::String &node, const Ogre::String &propertyName, const Ogre::String &value, const Ogre::String &type)
		: nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
};

class DotSceneLoader
{
public:
	DotSceneLoader() : mSceneMgr(0) {}
	virtual ~DotSceneLoader() {}
	void parseDotScene(const Ogre::String &SceneName, const Ogre::String &groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode = NULL, const Ogre::String &sPrependNode = "");

	Ogre::String getProperty(const Ogre::String &ndNm, const Ogre::String &prop);
	std::vector<nodeProperty> nodeProperties;
	std::vector<Ogre::String> staticObjects;
	std::vector<Ogre::String> dynamicObjects;

protected:
	void processScene(tinyxml2::XMLElement *XMLRoot);

	void processNodes(tinyxml2::XMLElement *XMLNode);
	void processExternals(tinyxml2::XMLElement *XMLNode);
	void processEnvironment(tinyxml2::XMLElement *XMLNode);
	void processTerrain(tinyxml2::XMLElement *XMLNode);
	void processUserDataReference(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent = 0);
	void processUserDataReference(tinyxml2::XMLElement *XMLNode, Ogre::Entity *pEntity);
	void processOctree(tinyxml2::XMLElement *XMLNode);
	void processLight(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent = 0);
	void processCamera(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent = 0);

	void processNode(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent = 0);
	void processLookTarget(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent);
	void processTrackTarget(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent);
	void processEntity(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent);
	void processParticleSystem(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent);
	void processBillboardSet(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent);
	void processPlane(tinyxml2::XMLElement *XMLNode, Ogre::SceneNode *pParent);

	void processFog(tinyxml2::XMLElement *XMLNode);
	void processSkyBox(tinyxml2::XMLElement *XMLNode);
	void processSkyDome(tinyxml2::XMLElement *XMLNode);
	void processSkyPlane(tinyxml2::XMLElement *XMLNode);
	void processClipping(tinyxml2::XMLElement *XMLNode);

	void processLightRange(tinyxml2::XMLElement *XMLNode, Ogre::Light *pLight);
	void processLightAttenuation(tinyxml2::XMLElement *XMLNode, Ogre::Light *pLight);

	Ogre::String getAttrib(tinyxml2::XMLElement *XMLNode, const char* parameter, const char* defaultValue = "");
	Ogre::Real getAttribReal(tinyxml2::XMLElement *XMLNode, const char* parameter, Ogre::Real defaultValue = 0);
	bool getAttribBool(tinyxml2::XMLElement *XMLNode, const char* parameter, bool defaultValue = false);

	Ogre::Vector3 parseVector3(tinyxml2::XMLElement *XMLNode);
	Ogre::Quaternion parseQuaternion(tinyxml2::XMLElement *XMLNode);
	Ogre::ColourValue parseColour(tinyxml2::XMLElement *XMLNode);

	Ogre::SceneManager *mSceneMgr;
	Ogre::SceneNode *mAttachNode;
	Ogre::String m_sGroupName;
	Ogre::String m_sPrependNode;
};

#endif // DOT_SCENELOADER_H
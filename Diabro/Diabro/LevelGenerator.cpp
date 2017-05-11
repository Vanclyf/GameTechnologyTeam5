#include "LevelGenerator.h"
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include "GameManager.h"
#include "math.h"

LevelGenerator::LevelGenerator():
scalar(1000)
{
	//create zone and generate dungeon
	_zone[0] = Zone(18, 18, 5, 5, 10, 500);
	
	drawDungeonFloor(_zone[0]);
}

LevelGenerator::~LevelGenerator()
{
}
/// returns empty position within dungeon
/// \param pEmptyNeighbours only returns positions with 8 emty neighbours
Coordinate LevelGenerator::getEmptyPosition(bool pEmptyNeighbours) {
	return _zone[0].getPosition(1, pEmptyNeighbours);
}

/// transfroms a world position to a grid coordinate
/// \param pWorldCoord coordinate in world position
Coordinate LevelGenerator::getGridPosition(Coordinate pWorldCoord) {
	int x = static_cast<int>(ceil(pWorldCoord.x / scalar + 0.0f));
	int z = static_cast<int>(ceil(pWorldCoord.z / scalar + 0.0f));

	return Coordinate(x,z);
}

/// transforms a grid coordinate to a world position
/// \param pGridCoord grid coordinate
Coordinate LevelGenerator::getWorldPosition(Coordinate pGridCoord) {
	return Coordinate(pGridCoord.x * scalar, pGridCoord.z * scalar);
}

/// retrieve zone
/// \param pZoneId coordinate of zone, within zone grid
Zone LevelGenerator::getZone(Coordinate pZoneId) {
	//TODO:implement multiple zones
	return _zone[0];
}

/// retrieve zone
/// \param pX x position of the zone
/// \param pZ z position of the zone
Zone LevelGenerator::getZone(int pX, int pZ) {
	//TODO:implement multiple zones
	return _zone[0];
}
/// creates a tile for each position in the zone

/// \param pZone zone from which to draw the tiles
void LevelGenerator::drawDungeonFloor(Zone pZone) {
	

	for (int ix = 0; ix < pZone.getResolution().x; ++ix) {
		for (int iz = 0; iz < pZone.getResolution().z; ++iz) {
			if (pZone.getTile(ix, iz) > 0) {
				Ogre::SceneNode* thisSceneNode = GameManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode();
				thisSceneNode->setPosition(ix * scalar, 0, iz * scalar);

				std::stringstream name;
				name << "tile_" << ix << "-" << iz;

				createPlane(name.str());

				Ogre::Entity* zoneEntity = GameManager::getSingleton().getSceneManager()->createEntity("entity: " + name.str(), name.str());
				zoneEntity->setMaterialName("Examples/Rockwall");
				thisSceneNode->attachObject(zoneEntity);
			}
		}
	}
}

/// creates a plane mesh using Ogre's Mesh manager
/// \param pName name of the plane (in format tile_x-z)
void LevelGenerator::createPlane(std::string pName)
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		pName,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		scalar, scalar, 2, 2,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);
}
/*
void LevelGenerator::createTileMesh(int pScalar, Coordinate pPosition, std::string pName) {
	//TODO: add uv coordinates

	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(pName, "General");

	Ogre::SubMesh* sub = mesh->createSubMesh();

	const float sqrt13 = 0.577350269f; /*sqrt(1/3)#1#
	int x = pPosition.x * pScalar;
	int y = 1;
	int z = pPosition.z * pScalar;

	//create vertices
	const size_t nVertices = 4;
	const size_t vBufCount = 3 * 2 * nVertices;
	float vertices[vBufCount] = {
		static_cast<float>(x + pScalar), static_cast<float>(y), static_cast<float>(z),			 //1
		sqrt13,  -sqrt13, -sqrt13,
		static_cast<float>(x), static_cast<float>(y), static_cast<float>(z),					 //2
		-sqrt13, -sqrt13, -sqrt13,
		static_cast<float>(x + pScalar), static_cast<float>(y), static_cast<float>(z + pScalar), //3
		sqrt13,  -sqrt13, sqrt13,
		static_cast<float>(x), static_cast<float>(y), static_cast<float>(z + pScalar),			 //4
		-sqrt13, -sqrt13, sqrt13,
	};

	Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
	Ogre::RGBA colours[nVertices];
	Ogre::RGBA* colorPtr = colours;

	//TODO: add colour per zone 
	Ogre::ColourValue col = Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f);

	rs->convertColourValue(col, colorPtr++); //0
	rs->convertColourValue(col, colorPtr++); //1
	rs->convertColourValue(col, colorPtr++); //2
	rs->convertColourValue(col, colorPtr++); //3

	//indices
	const size_t iBufCount = 6;
	unsigned short faces[iBufCount] = {
		0, 3, 2,
		1, 3, 0
	};

	mesh->sharedVertexData = new Ogre::VertexData();
	mesh->sharedVertexData->vertexCount = nVertices;

	Ogre::VertexDeclaration* vDeclaration = mesh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;
	//1th buffer
	//vertex description
	vDeclaration->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	vDeclaration->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	Ogre::HardwareVertexBufferSharedPtr vBuf =
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			offset, mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	vBuf->writeData(0, vBuf->getSizeInBytes(), vertices, true);

	Ogre::VertexBufferBinding* bind = mesh->sharedVertexData->vertexBufferBinding;
	bind->setBinding(0, vBuf);

	//2nd buffer
	offset = 0;
	vDeclaration->addElement(1, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);

	vBuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	vBuf->writeData(0, vBuf->getSizeInBytes(), colours, true);
	bind->setBinding(1, vBuf);

	Ogre::HardwareIndexBufferSharedPtr iBuf = Ogre::HardwareBufferManager::getSingleton().
		createIndexBuffer(
			Ogre::HardwareIndexBuffer::IT_16BIT,
			iBufCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	iBuf->writeData(0, iBuf->getSizeInBytes(), faces, true);

	sub->useSharedVertices = true;
	sub->indexData->indexBuffer = iBuf;
	sub->indexData->indexCount = iBufCount;
	sub->indexData->indexStart = 0;

	mesh->_setBounds(Ogre::AxisAlignedBox(x, y, z, x + pScalar, y + pScalar, z + pScalar));

	mesh->load();
}

void LevelGenerator::placeCity(City pCity, std::string pName, Ogre::ColourValue pColour) const {
	createCityMesh(pCity, 1000, pName, pColour);//scalar set to 1000 for size
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
		"Test/ColourTest", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_DIFFUSE);

	Ogre::Entity* testCity = GameManager::getSingleton().getSceneManager()->createEntity("pCity - " + pName, pName);
	testCity->setMaterialName("Test/ColourTest");

	Ogre::SceneNode* thisSceneNode = GameManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode();
	thisSceneNode->setPosition(-35, 0, 0);
	thisSceneNode->attachObject(testCity);
}

/// <summary>
/// Creates the a 3D mesh, representing the space around the pCity. (will however still be replaced)
/// </summary>
/// <param pName="pX">The pX position of the room.</param>
/// <param pName="pY">The pY position.</param>
/// <param pName="pZ">The pZ position.</param>
/// <param pName="pW">The width.</param>
/// <param pName="pH">The height.</param>
/// <param pName="pD">The depth.</param>
/// <param pName="pName">The pName.</param>
/// <param pName="pColour">The pColour.</param>
void LevelGenerator::createCityMesh(City pCity, int scalar, std::string pName, Ogre::ColourValue pColour) const {
	//TODO: generate as whole zone, so pathways are accounted for (will be new method)

	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(pName, "General");

	Ogre::SubMesh* sub = mesh->createSubMesh();

	const float sqrt13 = 0.577350269f; //sqrt(1/3)
	int x = pCity.position.x * scalar;
	int y = 1;
	int z = pCity.position.z * scalar;

	int w = pCity.width * scalar;
	int h = 1 * scalar;
	int d = pCity.depth * scalar;

	//create vertices
	const size_t nVertices = 8;
	const size_t vBufCount = 3 * 2 * nVertices;
	float vertices[vBufCount] = {
		static_cast<float>(x), static_cast<float>(y + h), static_cast<float>(z),         //0
		-sqrt13, sqrt13,  -sqrt13,
		static_cast<float>(x + w), static_cast<float>(y + h), static_cast<float>(z),     //1
		sqrt13,  sqrt13,  -sqrt13,
		static_cast<float>(x + w), static_cast<float>(y), static_cast<float>(z),         //2
		sqrt13,  -sqrt13, -sqrt13,
		static_cast<float>(x), static_cast<float>(y), static_cast<float>(z),		     //3
		-sqrt13, -sqrt13, -sqrt13,
		static_cast<float>(x), static_cast<float>(y + h), static_cast<float>(z + d),     //4
		-sqrt13, sqrt13,  sqrt13,
		static_cast<float>(x + w), static_cast<float>(y + h), static_cast<float>(z + d), //5
		sqrt13,  sqrt13,  sqrt13,
		static_cast<float>(x + w), static_cast<float>(y), static_cast<float>(z + d),	 //6
		sqrt13,  -sqrt13, sqrt13,
		static_cast<float>(x), static_cast<float>(y), static_cast<float>(z + d),	     //7
		-sqrt13, -sqrt13, sqrt13,
	};

	Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
	Ogre::RGBA colours[nVertices];
	Ogre::RGBA* colorPtr = colours;

	rs->convertColourValue(pColour, colorPtr++); //0
	rs->convertColourValue(pColour, colorPtr++); //1
	rs->convertColourValue(pColour, colorPtr++); //2
	rs->convertColourValue(pColour, colorPtr++); //3
	rs->convertColourValue(pColour, colorPtr++); //4
	rs->convertColourValue(pColour, colorPtr++); //5
	rs->convertColourValue(pColour, colorPtr++); //6
	rs->convertColourValue(pColour, colorPtr++); //7

	//indices
	const size_t iBufCount = 36;
	unsigned short faces[iBufCount] = {
		0, 3, 2,
		0, 2, 1,
		1, 2, 6,
		1, 6, 5,
		4, 5, 6,
		4, 6, 7,
		0, 4, 7,
		0, 7, 3,
		0, 1, 5,
		0, 5, 4,
		2, 3, 7,
		2, 7, 6
	};

	mesh->sharedVertexData = new Ogre::VertexData();
	mesh->sharedVertexData->vertexCount = nVertices;

	Ogre::VertexDeclaration* vDeclaration = mesh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;
	//1th buffer
	//vertex description
	vDeclaration->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	vDeclaration->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	Ogre::HardwareVertexBufferSharedPtr vBuf =
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			offset, mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	vBuf->writeData(0, vBuf->getSizeInBytes(), vertices, true);

	Ogre::VertexBufferBinding* bind = mesh->sharedVertexData->vertexBufferBinding;
	bind->setBinding(0, vBuf);

	//2nd buffer
	offset = 0;
	vDeclaration->addElement(1, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);

	vBuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	vBuf->writeData(0, vBuf->getSizeInBytes(), colours, true);
	bind->setBinding(1, vBuf);

	Ogre::HardwareIndexBufferSharedPtr iBuf = Ogre::HardwareBufferManager::getSingleton().
		createIndexBuffer(
			Ogre::HardwareIndexBuffer::IT_16BIT,
			iBufCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	iBuf->writeData(0, iBuf->getSizeInBytes(), faces, true);

	sub->useSharedVertices = true;
	sub->indexData->indexBuffer = iBuf;
	sub->indexData->indexCount = iBufCount;
	sub->indexData->indexStart = 0;

	mesh->_setBounds(Ogre::AxisAlignedBox(x, y, z, x + w, y + h, z + d));

	mesh->load();
}*/

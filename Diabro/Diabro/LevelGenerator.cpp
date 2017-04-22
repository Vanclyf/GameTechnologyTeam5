#include "LevelGenerator.h"
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include <OgreRoot.h>
#include <OgreHardwareBufferManager.h>
#include "GameManager.h"

LevelGenerator::LevelGenerator() 
{
	Zone z = Zone(30, 30, 4, 4, 10, 100);

	//place geometry for each city
	for (int i = 0; i < z.cities.size(); ++i) {
		City c = z.cities[i];
		
		//create unique city name (just a number)
		std::stringstream sstm; 
		sstm << "city-" << i;

		placeCity(c.x * 1000, 1, c.z * 1000, c.width * 1000, 1000, c.depth * 1000, sstm.str(), Ogre::ColourValue(0.5, 0.5, 0.5, 1.0));
	}
}

LevelGenerator::~LevelGenerator()
{
}

/// <summary>
/// Places a city-representing mesh.
/// </summary>
/// <param name="x">The x position of the city.</param>
/// <param name="y">The y position of the city.</param>
/// <param name="z">The z position of the city.</param>
/// <param name="w">The width of the city.</param>
/// <param name="h">The height of the city.</param>
/// <param name="d">The depth of the city.</param>
/// <param name="name">A unique name for the city.</param>
/// <param name="colour">The colour of the drawn cube.</param>
void LevelGenerator::placeCity(int x, int y, int z, int w, int h, int d, std::string name, Ogre::ColourValue colour) const {
	createCityMesh(x, y, z, w, h, d, name, colour);
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
		"Test/ColourTest", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_AMBIENT);

	Ogre::Entity* testCity = GameManager::getSingleton().getSceneManager()->createEntity("city - " + name, name);
	testCity->setMaterialName("Test/ColourTest");

	Ogre::SceneNode* thisSceneNode = GameManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode();
	thisSceneNode->setPosition(-35, 0, 0);
	thisSceneNode->attachObject(testCity);
}

/// <summary>
/// Creates the a 3D mesh, representing the space around the city. (will however still be replaced)
/// </summary>
/// <param name="x">The x position of the room.</param>
/// <param name="y">The y position.</param>
/// <param name="z">The z position.</param>
/// <param name="w">The width.</param>
/// <param name="h">The height.</param>
/// <param name="d">The depth.</param>
/// <param name="name">The name.</param>
/// <param name="colour">The colour.</param>
void LevelGenerator::createCityMesh(int x, int y, int z, int w, int h, int d, std::string name, Ogre::ColourValue colour) const {
	//TODO: generate as whole zone, so pathways are accounted for (will be new method)

	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(name, "General");

	Ogre::SubMesh* sub = mesh->createSubMesh();

	const float sqrt13 = 0.577350269f; /*sqrt(1/3)*/

	//create vertices
	const size_t nVertices = 8;
	const size_t vBufCount = 3 * 2 * nVertices;
	float vertices[vBufCount] = {
		x,       y + h,   z,		//0
		-sqrt13, sqrt13,  -sqrt13,
		x + w,   y + h,   z,		//1
		sqrt13,  sqrt13,  -sqrt13,
		x + w,   y,       z,		//2
		sqrt13,  -sqrt13, -sqrt13,
		x,       y,       z,		//3
		-sqrt13, -sqrt13, -sqrt13,
		x,       y + h,   z + d,	//4
		-sqrt13, sqrt13,  sqrt13,
		x + w,   y + h,   z + d,	//5
		sqrt13,  sqrt13,  sqrt13,
		x + w,   y,       z + d,	//6
		sqrt13,  -sqrt13, sqrt13,
		x,       y,       z + d,	//7
		-sqrt13, -sqrt13, sqrt13,
	};

	Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
	Ogre::RGBA colours[nVertices];
	Ogre::RGBA* colorPtr = colours;

	rs->convertColourValue(colour, colorPtr++); //0
	rs->convertColourValue(colour, colorPtr++); //1
	rs->convertColourValue(colour, colorPtr++); //2
	rs->convertColourValue(colour, colorPtr++); //3
	rs->convertColourValue(colour, colorPtr++); //4
	rs->convertColourValue(colour, colorPtr++); //5
	rs->convertColourValue(colour, colorPtr++); //6
	rs->convertColourValue(colour, colorPtr++); //7

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
}

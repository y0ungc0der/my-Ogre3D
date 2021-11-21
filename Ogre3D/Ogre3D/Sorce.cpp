//! [starter]

#pragma comment(lib, "OgreBites.lib")
#pragma comment(lib, "OgreRTShaderSystem.lib")

#include <exception>
#include <iostream>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include "OgreTrays.h"
#include "OgreRectangle2D.h"

using namespace Ogre;
using namespace OgreBites;

class TutorialApplication
	: public ApplicationContext
	, public InputListener
{
public:
	TutorialApplication();
	virtual ~TutorialApplication();

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
};


TutorialApplication::TutorialApplication()
	: ApplicationContext("OgreTutorialApp")
{
}


TutorialApplication::~TutorialApplication()
{
}


void TutorialApplication::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	Root* root = getRoot();
	SceneManager* scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// create the light
	Light* light = scnMgr->createLight("MainLight");
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	light->setDiffuseColour(1.0, 1.0, 1.0);
	light->setSpecularColour(1.0, 1.0, 1.0);
	lightNode->setPosition(320, 680, 1500);
	lightNode->attachObject(light);

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(75, 250, 1200);
	// and tell it to render into the main window
	Viewport * vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(ColourValue(0, 0, 0));
	cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

	Entity* ogreEntity = scnMgr->createEntity("sphere.mesh");
	SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(50, 445, 25));
	ogreEntity->setMaterialName("Examples/SphereMappedRustySteel");
	ogreNode->attachObject(ogreEntity);

	Entity* ogreEntity2 = scnMgr->createEntity("sphere.mesh");
	SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
	ogreEntity2->setMaterialName("Examples/SphereMappedRustySteel");
	ogreNode2->setPosition(250, 450, 250);
	ogreNode2->attachObject(ogreEntity2);

	Entity* ogreEntity3 = scnMgr->createEntity("cube.mesh");
	SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
	ogreEntity3->setMaterialName("Examples/Rockwall");
	ogreNode3->setScale(1.5, 1.5, 1.5);
	ogreNode3->setPosition(270, 90, 350);
	ogreNode3->attachObject(ogreEntity3);

	Entity* ogreEntity4 = scnMgr->createEntity("sphere.mesh");
	SceneNode* ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();
	ogreEntity4->setMaterialName("Examples/SphereMappedRustySteel");
	ogreNode4->setPosition(-127, 348, 0);
	ogreNode4->setScale(0.5, 0.5, 0.5);
	ogreNode4->attachObject(ogreEntity4);

	Entity* ogreEntity5 = scnMgr->createEntity("cube.mesh");
	SceneNode* ogreNode5 = scnMgr->getRootSceneNode()->createChildSceneNode();
	ogreEntity5->setMaterialName("Examples/Rockwall");
	ogreNode5->setScale(0.25, 0.25, 0.25);
	ogreNode5->setPosition(-205, 30, 425);
	ogreNode5->attachObject(ogreEntity5);

	// [robot]
	Entity* robotEntity = scnMgr->createEntity("robot.mesh");
	SceneNode* ogreNode6 = scnMgr->getRootSceneNode()->createChildSceneNode();
	robotEntity->setCastShadows(true);
	ogreNode6->setScale(Vector3(3, 3, 3));
	ogreNode6->setPosition(0, 0, 500);
	ogreNode6->yaw(Degree(-60));
	ogreNode6->attachObject(robotEntity);
	//! [robot]

	//! [plane]
	Plane plane(Vector3::UNIT_Y, 0);
	//! [plane]

	//! [planedefine]
	MeshManager::getSingleton().createPlane(
		"ground", RGN_DEFAULT,
		plane,
		3000, 1500, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);
	//! [planedefine]

	//! [planecreate]
	Entity* groundEntity = scnMgr->createEntity("ground");
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/BeachStones");
	//! [planesetmat]
	
	scnMgr->setSkyBox(true, "Examples/EarlyMorningSkyBox");

	ParticleSystem* smokesParticle = scnMgr->createParticleSystem("Smokes", "Examples/Smoke");
	SceneNode* particleNode = scnMgr->getRootSceneNode()->createChildSceneNode("Particle");
	particleNode->setPosition(ogreNode6->getPosition());
	particleNode->attachObject(smokesParticle);

	ParticleSystem* fountainParticle = scnMgr->createParticleSystem("Fountain", "Examples/PurpleFountain");
	SceneNode* particleNode1 = scnMgr->getRootSceneNode()->createChildSceneNode("Particle1");
	particleNode1->setPosition(ogreNode3->getPosition());
	particleNode1->attachObject(fountainParticle);

	ParticleSystem* AureolaParticle1 = scnMgr->createParticleSystem("Aureola1", "Examples/Aureola");
	SceneNode* particleNode2 = scnMgr->getRootSceneNode()->createChildSceneNode("Particle2");
	particleNode2->setPosition(ogreNode2->getPosition());
	particleNode2->attachObject(AureolaParticle1);

	ParticleSystem* NimbusParticle = scnMgr->createParticleSystem("Nimbus", "Examples/GreenyNimbus");
	SceneNode* particleNode3 = scnMgr->getRootSceneNode()->createChildSceneNode("Particle3");
	particleNode3->setPosition(ogreNode5->getPosition());
	particleNode3->attachObject(NimbusParticle);

	ParticleSystem* AureolaParticle2 = scnMgr->createParticleSystem("Aureola2", "Examples/Aureola");
	SceneNode* particleNode4 = scnMgr->getRootSceneNode()->createChildSceneNode("Particle4");
	particleNode4->setPosition(ogreNode->getPosition());
	particleNode4->attachObject(AureolaParticle2);

	ParticleSystem* AureolaParticle3 = scnMgr->createParticleSystem("Aureola3", "Examples/Aureola");
	SceneNode* particleNode5 = scnMgr->getRootSceneNode()->createChildSceneNode("Particle5");
	particleNode5->setPosition(ogreNode4->getPosition());
	particleNode5->attachObject(AureolaParticle3);	
}


bool TutorialApplication::keyPressed(const KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	return true;
}


int main(int argc, char **argv)
{
	try
	{
		TutorialApplication app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

//! [starter]
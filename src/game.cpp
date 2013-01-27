#include "client/gui.h"
#include "client/input.h"
#include "entity.h"
#include "game.h"
#include "log.h"

using namespace TNL;

const float Game::HEIGHTMAP_SIZE = 500.0;

Game::Game(bool server)
{
    mServer = server;
    Game();
    setMsgTypes(LogNetConnection | LogFatalError | LogError | LogWarning);
}

Game::Game()
{
}

Game::~Game()
{
    for(int i; i < mEntities.size(); i++)
    {
        delete mEntities[i];
    }
}

/**
 * @brief perform \t milliseconds of simulation
 */
void Game::update(U32 t)
{
    // TODO: check return value
    mDevice->run();

    mDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
    mSceneManager->drawAll();
    //Gui::get()->draw();
    mDriver->endScene();
}

/**
 * @brief initialize
 */
void Game::initialize()
{
    mDevice = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480), 16,
                                false, false, false, Input::get());
    if(!mDevice)
    {
        // handle no device found
    }

    mDriver = mDevice->getVideoDriver();

    // resource loading
    mSceneManager = mDevice->getSceneManager();
    mMesh = mSceneManager->getMesh("../resource/warrior.x");

    // create terrain
    mTerrain = mSceneManager->addTerrainSceneNode("../resource/heightmap.bmp",
                                                  0,
                                                  -1,
                                                  irr::core::vector3df(0.0, 0.1, 0.0),
                                                  irr::core::vector3df(0.0,   0.0, 0.0),
                                                  irr::core::vector3df(1.0 / HEIGHTMAP_SIZE, 1.0 / HEIGHTMAP_SIZE * 0.05, 1.0/ HEIGHTMAP_SIZE),
                                                  irr::video::SColor(255, 255, 255, 255),
                                                  5,
                                                  irr::scene::ETPS_17,
                                                  4
                                                  );


    mTerrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    mTerrain->setMaterialTexture(0, mDriver->getTexture("../resource/dirt.jpg"));
    mTerrain->scaleTexture(10.0, 10.0);

}

void Game::addEntity(Entity *entity)
{
    irr::scene::IAnimatedMeshSceneNode *node;
    // TODO: get mesh from entity (i.e. entity->getModel() or similar)
    node = mSceneManager->addAnimatedMeshSceneNode(mMesh);
    entity->setNode(node);

    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMD2Animation(irr::scene::EMAT_STAND);
    node->setMaterialTexture(0, mDriver->getTexture("../resource/warrior.jpg"));
    node->setScale(vector3df(0.01));

    // create triangle selector for the terrain
    irr::scene::ITriangleSelector* selector
        = mSceneManager->createTerrainTriangleSelector(mTerrain, 0);
    mTerrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the node
    irr::scene::ISceneNodeAnimator* anim = mSceneManager->createCollisionResponseAnimator(
        selector, node, vector3df(0.01),
        vector3df(0,-0.1,0),
        vector3df(0,0,0));
    selector->drop();
    node->addAnimator(anim);
    anim->drop();

    mEntities.push_back(entity);
}

Vector<SafePtr<Entity> >* Game::getEntities()
{
    return &mEntities;
}

void Game::writeString(const char *s)
{
    Log::p(s);
}

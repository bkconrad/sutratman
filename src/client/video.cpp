#include "video.h"
#include "entity.h"
#include "entity_node.h"

Video::Video(irr::IEventReceiver* eventReceiver)
   : mEventReceiver(eventReceiver)
{
   mDevice = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480), 16,
            false, false, false, eventReceiver);
   if(!mDevice) {
      // handle no device found
   }

   mDevice->setWindowCaption(L"Sutratman");
   mDriver = mDevice->getVideoDriver();
   mSceneManager = mDevice->getSceneManager();
   mGuiEnv = mDevice->getGUIEnvironment();
   mGuiEnv->addStaticText(L"Hi!", irr::core::rect<irr::s32>(10, 10, 260, 22), true);
   mMesh = mSceneManager->getMesh("../resource/boxman.x");
   mCamera = mSceneManager->addCameraSceneNode(0, irr::core::vector3df(0,3,5), irr::core::vector3df(0,5,0));

}

/** @return true if the video system can continue running
  */
bool Video::run()
{
   for(int i = 0; i < mEntityNodes.size(); i++) {
      mEntityNodes[i]->update();
   }

   // center on the focus entity if we have one
   if (mFocusEntity.isValid()) {
      Vec2 pos = mFocusEntity->getPos();
      mCamera->setTarget(irr::core::vector3df(pos.x * 10.0, pos.y * 10.0, 0.0));
      mCamera->setPosition(irr::core::vector3df(pos.x * 10.0 + 3.0, pos.y * 10.0 + 3.0, 5.0));
   }

   if(!mDevice->run()) {
      return false;
   }
   mDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
   mSceneManager->drawAll();
   mGuiEnv->drawAll();
   mDriver->endScene();
}

/** @brief addEntity
  *
  * @todo: document this function
  */
void Video::addEntity(Entity* entity)
{
   if (entity->isControlled()) {
      mFocusEntity = entity;
   }
   irr::scene::IAnimatedMeshSceneNode* node = mSceneManager->addAnimatedMeshSceneNode(mMesh);
   node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
   EntityNode* entityNode = new EntityNode(entity, node);
   mEntityNodes.push_back(entityNode);
//   node->setMD2Animation(scene::EMAT_STAND);
//   node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
}

Video::~Video()
{
   for (int i; i < mEntityNodes.size(); i++) {
      delete mEntityNodes[i];
   }
   mDevice->drop();
}

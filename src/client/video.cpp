#include "video.h"
#include "entity.h"
#include "entity_node.h"
#include "input.h"

Video* Video::mInstance = NULL;
const float Video::VIDEOSCALE = 10.0;

Video* Video::get()
{
   return mInstance ? mInstance : new Video();
}

Video::Video()
{
   mInstance = this;

   mDevice = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480), 16,
            false, false, false, Input::get());
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
      vec2 pos = mFocusEntity->getPos();
      vec2 rot = mFocusEntity->getRot();
      vec2 cameraOffset;
      cameraOffset = vec2(cos(rot.y), sin(rot.y));
      cameraOffset *= 3.0;
      mCamera->setTarget(irr::core::vector3df(pos.x * Video::VIDEOSCALE, pos.y * Video::VIDEOSCALE, 0.0));
      mCamera->bindTargetAndRotation(true);
      mCamera->setPosition(irr::core::vector3df(pos.x * Video::VIDEOSCALE + cameraOffset.x, pos.y * Video::VIDEOSCALE, cameraOffset.y));
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

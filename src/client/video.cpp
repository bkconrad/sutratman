#include "video.h"
#include "entity.h"
#include "entity_node.h"
#include "client/gui.h"
#include "mathutil.h"
#include "input.h"

#include "diagnostics.h"

#include <glm/glm.hpp>

using glm::clamp;

using namespace mathutil;

Video* Video::mInstance = NULL;
const float Video::VIDEOSCALE = 10.0;
const float Video::CAMERA_ACCELERATION = 0.001;
const float Video::CAMERA_MAX_SPEED = 0.1;

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

    // window setup
   mDevice->setWindowCaption(L"Sutratman");
   mDriver = mDevice->getVideoDriver();

   // resource loading
   mSceneManager = mDevice->getSceneManager();
   mMesh = mSceneManager->getMesh("../resource/warrior.x");

   // starting camera position
   mCameraRotation = 0.0;
   mCameraVelocity = 0.0;
   mCamera = mSceneManager->addCameraSceneNode(0, irr::core::vector3df(0,3,5), irr::core::vector3df(0,5,0));

   irr::gui::IGUIEnvironment *guiEnv = mDevice->getGUIEnvironment();
   Gui::get()->init(guiEnv);
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
      vec3 pos = mFocusEntity->getPos();
      vec3 rot = mFocusEntity->getRot() * RADIANS;

      DIAG(position, pos);
      DIAG(rotation, rot);

      float positiveAngularDistance = mod(rot.y - mCameraRotation, RADIANS);
      float negativeAngularDistance = mod(mCameraRotation - rot.y, RADIANS);
      float minimumAngularDistance = min(positiveAngularDistance, negativeAngularDistance);
      if (minimumAngularDistance > RADIANS / 64.0) {
         mCameraVelocity += positiveAngularDistance > negativeAngularDistance ? -CAMERA_ACCELERATION : CAMERA_ACCELERATION;
         mCameraVelocity = clamp(mCameraVelocity, -CAMERA_MAX_SPEED, CAMERA_MAX_SPEED);
         mCameraRotation += mCameraVelocity;
         mCameraRotation = mod(mCameraRotation, RADIANS);
      } else {
         mCameraVelocity = 0.0;
      }

      vec2 cameraOffset(sin(mCameraRotation), cos(mCameraRotation));
      cameraOffset *= 3.0;

      mCamera->setTarget(irr::core::vector3df(pos.x * Video::VIDEOSCALE, pos.y * Video::VIDEOSCALE + 1.0, pos.z * Video::VIDEOSCALE));
      mCamera->bindTargetAndRotation(true);
      mCamera->setPosition(irr::core::vector3df(pos.x * Video::VIDEOSCALE + cameraOffset.x, pos.y * Video::VIDEOSCALE + 2.0, pos.z * Video::VIDEOSCALE + cameraOffset.y));
   }

   if(!mDevice->run()) {
      return false;
   }
   mDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
   mSceneManager->drawAll();
   Gui::get()->draw();
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
//   node->setScale(irr::core::vector3df(0.01, 0.01, 0.01));
   node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
   node->setMD2Animation(irr::scene::EMAT_STAND);
   node->setMaterialTexture( 0, mDriver->getTexture("../resource/warrior.jpg") );
   EntityNode* entityNode = new EntityNode(entity, node);
   mEntityNodes.push_back(entityNode);
}

Video::~Video()
{
   for (int i; i < mEntityNodes.size(); i++) {
      delete mEntityNodes[i];
   }
   mDevice->drop();
}

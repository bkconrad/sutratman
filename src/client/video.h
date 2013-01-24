#ifndef SUT_VIDEO_H
#define SUT_VIDEO_H

#include <irrlicht.h>
#include <tnl.h>
#include <tnlNetBase.h>

using namespace TNL;

class EntityNode;
class Entity;
class Video
{
   public:
      static const float VIDEOSCALE; // scale from normalized simulation positions to irrlich positions
      static const float ROTATESPEED; // speed of camera movement

      static Video* get();

      bool run();
      void addEntity(Entity* entity);

   private:
      Video();
      virtual ~Video();

      static Video* mInstance;
      float mCameraRotation; // camera's rotation around the y axis
      SafePtr<Entity> mFocusEntity;
      Vector<EntityNode*> mEntityNodes;

      irr::IEventReceiver *mEventReceiver;
      irr::IrrlichtDevice *mDevice;
      irr::gui::IGUIEnvironment *mGuiEnv;
      irr::scene::ISceneManager *mSceneManager;
      irr::video::IVideoDriver *mDriver;
      irr::scene::IAnimatedMesh *mMesh;
      irr::scene::ICameraSceneNode *mCamera;
};

#endif // SUT_VIDEO_H

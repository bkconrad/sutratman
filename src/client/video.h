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
      explicit Video(irr::IEventReceiver* eventReceiver = NULL);
      virtual ~Video();
      bool run();
      void addEntity(Entity* entity);
   protected:
   private:
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

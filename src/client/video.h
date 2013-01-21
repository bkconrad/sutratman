#ifndef SUT_VIDEO_H
#define SUT_VIDEO_H

#include <irrlicht.h>
#include <tnl.h>

using namespace TNL;

class EntityNode;
class Entity;
class Video
{
   public:
      Video(irr::IEventReceiver* eventReceiver);
      virtual ~Video();
      bool run();
      void addEntity(Entity* entity);
   protected:
   private:
      Vector<EntityNode*> mEntityNodes;

      irr::IEventReceiver *mEventReceiver;
      irr::IrrlichtDevice *mDevice;
      irr::gui::IGUIEnvironment *mGuiEnv;
      irr::scene::ISceneManager *mSceneManager;
      irr::video::IVideoDriver *mDriver;
      irr::scene::IAnimatedMesh *mMesh;
};

#endif // SUT_VIDEO_H

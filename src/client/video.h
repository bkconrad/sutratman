#ifndef SUT_VIDEO_H
#define SUT_VIDEO_H

#include <irrlicht.h>

class Entity;
class Video
{
   public:
      Video();
      virtual ~Video();
      bool run();
      void addEntity(Entity* entity);
   protected:
   private:
      irr::IrrlichtDevice *mDevice;
      irr::gui::IGUIEnvironment *mGuiEnv;
      irr::scene::ISceneManager *mSceneManager;
      irr::video::IVideoDriver *mDriver;
      irr::scene::IAnimatedMesh *mMesh;
};

#endif // SUT_VIDEO_H

#ifndef SUT_VIDEO_H
#define SUT_VIDEO_H

#include <irrlicht.h>

class Video
{
   public:
      Video();
      virtual ~Video();
      bool run();
   protected:
   private:
      irr::IrrlichtDevice *mDevice;
      irr::gui::IGUIEnvironment *mGuiEnv;
      irr::scene::ISceneManager *mSceneManager;
      irr::video::IVideoDriver *mDriver;
};

#endif // SUT_VIDEO_H

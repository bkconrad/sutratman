#include "video.h"

Video::Video()
{
   mDevice = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(640, 480), 16,
            false, false, false, 0);
   if(!mDevice) {
      // handle no device found
   }

   mDevice->setWindowCaption(L"Sutratman");
   mDriver = mDevice->getVideoDriver();
   mSceneManager = mDevice->getSceneManager();
   mGuiEnv = mDevice->getGUIEnvironment();
   mGuiEnv->addStaticText(L"Hi!", irr::core::rect<irr::s32>(10, 10, 260, 22), true);
}

/** @return true if the video system can continue running
  */
bool Video::run()
{
   if(!mDevice->run()) {
      return false;
   }
   mDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
   mSceneManager->drawAll();
   mGuiEnv->drawAll();
   mDriver->endScene();
}



Video::~Video()
{
   mDevice->drop();
}

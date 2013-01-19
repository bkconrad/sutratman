#ifndef SUT_VIDEO_H
#define SUT_VIDEO_H

#ifndef SUT_DEDICATED
   #include <irrlicht.h>
   using namespace irr;
   using namespace core;
   using namespace scene;
   using namespace video;
   using namespace io;
   using namespace gui;
#endif

class Video
{
   public:
      Video();
      virtual ~Video();
   protected:
   private:
};

#endif // SUT_VIDEO_H

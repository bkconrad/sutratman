#include "video.h"

Video::Video()
{
      IrrlichtDevice *device =
         createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
               false, false, false, 0);
}

Video::~Video()
{
   //dtor
}

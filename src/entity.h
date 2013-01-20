#ifndef ENTITY_H
#define ENTITY_H

#include "vec2.h"
#include <tnlNetObject.h>

using namespace TNL;

class Entity : public NetObject
{
   public:
      Entity();
      virtual ~Entity();
   protected:
   private:
      Vec2 mPos;
};

#endif // ENTITY_H

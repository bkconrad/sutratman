#ifndef GAME_H
#define GAME_H

#include "entity.h"

#include <tnl.h>

using namespace TNL;

class Game
{
   public:
      Game();
      virtual ~Game();
   protected:
   private:
      Vector<SafePtr<Entity> > mEntities;
};

#endif // GAME_H

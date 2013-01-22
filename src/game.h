#ifndef GAME_H
#define GAME_H

#include <tnl.h>
#include <tnlLog.h>
#include <tnlNetBase.h>

using namespace TNL;

class Entity;
class Game : LogConsumer
{
   public:
      explicit Game(bool server);
      Game();
      virtual ~Game();
      virtual void addEntity(Entity* entity);
      Vector<SafePtr<Entity> >* getEntities();

      // overrides
      void writeString(const char*);

   protected:
   private:
      bool mServer;
      Vector<SafePtr<Entity> > mEntities;
};

#endif // GAME_H

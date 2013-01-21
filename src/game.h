#ifndef GAME_H
#define GAME_H

#include <tnl.h>

using namespace TNL;

class Entity;
class Game
{
   public:
      explicit Game(bool server);
      Game();
      virtual ~Game();
      virtual void addEntity(Entity* entity);
      Vector<Entity*>* getEntities();
   protected:
   private:
      bool mServer;
      Vector<Entity*> mEntities;
};

#endif // GAME_H

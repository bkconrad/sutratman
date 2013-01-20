#ifndef ENTITY_H
#define ENTITY_H

#include "vec2.h"
#include <tnl.h>
#include <tnlNetObject.h>
#include <tnlGhostConnection.h>

using namespace TNL;

class Game;
class Entity : public NetObject
{
   public:
      TNL_DECLARE_CLASS(Entity);
      Entity(Game* game);
      Entity();
      bool onGhostAdd(GhostConnection* connection);
      void performScopeQuery(GhostConnection* connection);
      virtual ~Entity();
   protected:
   private:
      Game* mGame;
      Vec2 mPos;
};

#endif // ENTITY_H

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
      virtual ~Entity();

      // overrides
      bool onGhostAdd(GhostConnection* connection);
      void performScopeQuery(GhostConnection* connection);
      virtual U32 packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream);
      virtual void unpackUpdate(GhostConnection* connection, BitStream* bitStream);

      void setPos(float x, float y);
      void setPos(Vec2& pos);
      const Vec2& getPos();

   protected:
   private:
      Game* mGame;
      Vec2 mPos;
};

#endif // ENTITY_H

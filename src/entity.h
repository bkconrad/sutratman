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
      Entity(Game* game = NULL);
      virtual ~Entity();

      // overrides
      bool onGhostAdd(GhostConnection* connection);
      void performScopeQuery(GhostConnection* connection);
      virtual U32 packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream);
      virtual void unpackUpdate(GhostConnection* connection, BitStream* bitStream);

      void setGame(Game* game);
      void setPos(float x, float y);
      void setPos(const Vec2& pos);
      void modPos(const Vec2& pos);
      const Vec2& getPos();

      enum MaskBits {
         InitialMask = 1 << 0,
         PositionMask = 1 << 1,
      };

   protected:
   private:
      static int IdIndex;
      U32 mId;
      Game* mGame;
      Vec2 mPos;

      // client only. true if this is the entity we control
      bool mIsControlled;
};

#endif // ENTITY_H

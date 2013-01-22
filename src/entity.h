#ifndef ENTITY_H
#define ENTITY_H

#include "vec2.h"
#include <tnl.h>
#include <tnlNetObject.h>
#include <tnlGhostConnection.h>

/**
these macros allow decoupling of client and server code by selectively
defining method stubs in dedicated server builds. this allows
definition of those methods in the corresponding client/* files for
client-enabled builds
*/
#define SUT_DECLARE_GAME_ENTITY(klass) \
   TNL_DECLARE_CLASS(klass); \
   virtual bool onGhostAdd(GhostConnection* connection); \
   virtual void unpackUpdate(GhostConnection* connection, BitStream* bitStream) \

#ifdef SUT_DEDICATED

   #define SUT_IMPLEMENT_GAME_ENTITY(klass) \
      TNL_IMPLEMENT_NETOBJECT(klass); \
      void klass::unpackUpdate(GhostConnection* c, BitStream* b) { } \
      bool klass::onGhostAdd(GhostConnection* c) { return true; }

#else

   #define SUT_IMPLEMENT_GAME_ENTITY(klass) \
      TNL_IMPLEMENT_NETOBJECT(klass);

#endif

using namespace TNL;

class Game;
class Entity : public NetObject
{
   public:
      TNL_DECLARE_CLASS(Entity);
      Entity(Game* game = NULL);
      virtual ~Entity();

      // overrides
      virtual bool onGhostAdd(GhostConnection* connection);
      virtual void performScopeQuery(GhostConnection* connection);
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
      Game* mGame;

      // client only. true if this is the entity we control
      bool mIsControlled;
      static int IdIndex;
      U32 mId;
      Vec2 mPos;

   private:
};

#endif // ENTITY_H

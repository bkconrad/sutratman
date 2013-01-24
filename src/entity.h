#ifndef ENTITY_H
#define ENTITY_H

#include <tnl.h>
#include <tnlNetObject.h>
#include <tnlGhostConnection.h>

#include <glm/glm.hpp>

#include <gtest/gtest_prod.h>

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
using namespace glm;

class Game;
class ClientGame;
class Entity : public NetObject
{
   public:
      TNL_DECLARE_CLASS(Entity);
      TNL_DECLARE_RPC(c2sMove, (F32 angle));
      TNL_DECLARE_RPC(c2sRotate, (F32 angle));

      // TODO should be replaced with stats or something
      static const float MOVESPEED;

      Entity(Game* game = NULL);
      virtual ~Entity();

      // entity-specific things
      virtual bool isConsistentWith(const Entity& entity);

      // overrides
      virtual bool onGhostAdd(GhostConnection* connection);
      virtual void performScopeQuery(GhostConnection* connection);
      virtual U32 packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream);
      virtual void unpackUpdate(GhostConnection* connection, BitStream* bitStream);

      bool isControlled();
      void setControlled(bool controlled);
      const vec3& getPos();
      void setPos(float x, float y, float z);
      void setPos(const vec3& pos);
      void modPos(const vec3& pos);
      const vec3& getRot();
      void setRot(const vec3& rot);
      void modRot(const vec3& rot);

      enum MaskBits {
         InitialMask = 1 << 0,
         PositionMask = 1 << 1,
         RotationMask = 1 << 2,
      };

   protected:
      Game* mGame;

      static int IdIndex;
      U32 mId;
      vec3 mPos;
      vec3 mRot; // in radians, math angle

      // client only
      ClientGame* mClientGame;
      bool mIsControlled;
   private:
      FRIEND_TEST(entity, packing);
};

#endif // ENTITY_H

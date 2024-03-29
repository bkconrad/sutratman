#ifndef MOBILE_ENTITY_H_
#define MOBILE_ENTITY_H_

#include "entity.h"
#include "mobile_entity_animator.h"

#include <gtest/gtest.h>
#include <irrlicht.h>

using irr::core::vector3df;

class MobileEntity : public Entity
{
   using Entity::isConsistentWith;
   
   typedef Entity Parent;
public:
   TNL_DECLARE_CLASS(MobileEntity);
   MobileEntity();
   ~MobileEntity();
   bool isConsistentWith(const MobileEntity& entity);
   void onGhostAddBeforeUpdate(GhostConnection* connection);
   U32 packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream);
   void performScopeQuery(GhostConnection* connection);
   void unpackUpdate(GhostConnection* connection, BitStream* bitStream);

   void detectCollisionWith(irr::scene::ITriangleSelector* selector, irr::scene::ISceneManager* smgr);
   void moveTo(vector3df target);
   
   // overrides
   virtual void update();
   
protected:
   vector3df mVelocity;
   vector3df mMovementDirection;
   irr::scene::ISceneNodeAnimator *mMoveAnimator;
   MobileEntityAnimator *mCollisionAnimator;
   
   FRIEND_TEST(mobile_entity, packing);
};

#endif // MOBILE_ENTITY_H_

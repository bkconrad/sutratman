#ifndef MOBILE_ENTITY_H_
#define MOBILE_ENTITY_H_

#include "entity.h"
#include "mobile_entity_animator.h"

#include <irrlicht.h>

using irr::core::vector3df;

class MobileEntity : public Entity
{
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
   irr::scene::ISceneNodeAnimator *mMoveAnimator;
   MobileEntityAnimator *mCollisionAnimator;
};

#endif // MOBILE_ENTITY_H_

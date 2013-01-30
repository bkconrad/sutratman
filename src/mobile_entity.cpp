#include "diagnostics.h"
#include "game.h"
#include "mobile_entity.h"

TNL_IMPLEMENT_NETOBJECT(MobileEntity);

MobileEntity::MobileEntity()
   : mVelocity(0), mMoveAnimator(NULL)
{
}

MobileEntity::~MobileEntity()
{
}

bool MobileEntity::isConsistentWith(const MobileEntity& entity)
{
   return mVelocity == entity.mVelocity
       && Parent::isConsistentWith(entity);
}

bool MobileEntity::onGhostAdd(GhostConnection* connection)
{
   Parent::onGhostAdd(connection);
}

U32 MobileEntity::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream)
{
   Parent::packUpdate(connection, updateMask, bitStream);
   if(bitStream->writeFlag(updateMask & VelocityMask)) {
        bitStream->writeFloat(mVelocity.X / 2.0 + 0.5, 16);
        bitStream->writeFloat(mVelocity.Y / 2.0 + 0.5, 16);
        bitStream->writeFloat(mVelocity.Z / 2.0 + 0.5, 16);
   }
   return 0;
}

void MobileEntity::unpackUpdate(GhostConnection* connection, BitStream* bitStream)
{
   Parent::unpackUpdate(connection, bitStream);
   if(bitStream->readFlag()) {
        mVelocity.X = (bitStream->readFloat(16) - 0.5) * 2.0;
        mVelocity.Y = (bitStream->readFloat(16) - 0.5) * 2.0;
        mVelocity.Z = (bitStream->readFloat(16) - 0.5) * 2.0;
        
         moveTo(mLastKnownPosition + mVelocity);
   }
}

void MobileEntity::performScopeQuery(GhostConnection* connection)
{
   Parent::performScopeQuery(connection);
}

void MobileEntity::update()
{
   // setPos(mLastKnownPosition + mVelocity * (TNL::Platform::getRealMilliseconds() - mLastUpdate));
}

void MobileEntity::moveTo(vector3df target)
{
   if(mMoveAnimator) {
     mNode->removeAnimator(mMoveAnimator);
     mMoveAnimator = NULL;
   }
   if (mGame && mNode) {
   mMoveAnimator = mGame->getSceneManager()->createFlyStraightAnimator(
      mLastKnownPosition, target, 1000);
      DIAG("from", mLastKnownPosition);
      DIAG("to", target);
      mNode->addAnimator(mMoveAnimator);
   }
}

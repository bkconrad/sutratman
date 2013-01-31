#include "diagnostics.h"
#include "game.h"
#include "mobile_entity.h"

TNL_IMPLEMENT_NETOBJECT(MobileEntity);

MobileEntity::MobileEntity()
   : mVelocity(0), mMoveAnimator(NULL), mCollisionAnimator(NULL)
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

void MobileEntity::onGhostAddBeforeUpdate(GhostConnection* connection)
{
   Parent::onGhostAddBeforeUpdate(connection);
}

U32 MobileEntity::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream)
{
   Parent::packUpdate(connection, updateMask, bitStream);
   if(bitStream->writeFlag(updateMask & VelocityMask)) {
         vector3df vel = mCollisionAnimator->getActualVelocity();
        bitStream->writeFloat(vel.X / (2.0 * Game::CELL_SIZE) + 0.5, FLOATSIZE);
        bitStream->writeFloat(vel.Y / (2.0 * Game::CELL_SIZE) + 0.5, FLOATSIZE);
        bitStream->writeFloat(vel.Z / (2.0 * Game::CELL_SIZE) + 0.5, FLOATSIZE);
   }
   if(bitStream->writeFlag(updateMask & VelocityMask)) {
        bitStream->writeFloat(mVelocity.X / (2.0 * Game::CELL_SIZE) + 0.5, FLOATSIZE);
        bitStream->writeFloat(mVelocity.Y / (2.0 * Game::CELL_SIZE) + 0.5, FLOATSIZE);
        bitStream->writeFloat(mVelocity.Z / (2.0 * Game::CELL_SIZE) + 0.5, FLOATSIZE);
   }
   return 0;
}

void MobileEntity::unpackUpdate(GhostConnection* connection, BitStream* bitStream)
{
   Parent::unpackUpdate(connection, bitStream);
   if(bitStream->readFlag()) {
      vector3df vel;
        vel.X = (bitStream->readFloat(FLOATSIZE) - 0.5) * (2.0 * Game::CELL_SIZE);
        vel.Y = (bitStream->readFloat(FLOATSIZE) - 0.5) * (2.0 * Game::CELL_SIZE);
        vel.Z = (bitStream->readFloat(FLOATSIZE) - 0.5) * (2.0 * Game::CELL_SIZE);
         mCollisionAnimator->setActualVelocity(vel);
   }
   if(bitStream->readFlag()) {
        mVelocity.X = (bitStream->readFloat(FLOATSIZE) - 0.5) * (2.0 * Game::CELL_SIZE);
        mVelocity.Y = (bitStream->readFloat(FLOATSIZE) - 0.5) * (2.0 * Game::CELL_SIZE);
        mVelocity.Z = (bitStream->readFloat(FLOATSIZE) - 0.5) * (2.0 * Game::CELL_SIZE);
        mCollisionAnimator->setVelocity(mVelocity);
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
//   if(mMoveAnimator) {
//     mNode->removeAnimator(mMoveAnimator);
//     mMoveAnimator->drop();
//     mMoveAnimator = NULL;
//   }
//   if (mGame && mNode) {
//   mMoveAnimator = mGame->getSceneManager()->createFlyStraightAnimator(
//      mLastKnownPosition, target, 1000);
//      DIAG("from", mLastKnownPosition);
//      DIAG("to", target);
//      mNode->addAnimator(mMoveAnimator);
//   }
   if (mCollisionAnimator) {
      mCollisionAnimator->setVelocity(target - mLastKnownPosition);
   }
}

void MobileEntity::detectCollisionWith(irr::scene::ITriangleSelector* selector, irr::scene::ISceneManager *smgr)
{
   mCollisionAnimator = new MobileEntityAnimator(smgr, selector, mNode,
   vector3df(0.1), vector3df(0, -0.1, 0));
   mNode->addAnimator(mCollisionAnimator);
}

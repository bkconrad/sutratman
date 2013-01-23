#include "entity.h"
#include "game.h"
#include "game_interface.h"
#include "log.h"

#include <tnlBitStream.h>

using namespace TNL;

int Entity::IdIndex = 1;

TNL_IMPLEMENT_NETOBJECT(Entity);

TNL_IMPLEMENT_NETOBJECT_RPC(Entity, c2sMove, (), (),
NetClassGroupAllMask,  RPCGuaranteedOrdered, RPCToGhostParent, 0)
{
   // TODO check client's ownership
   modPos(Vec2(.01, .01));
   setMaskBits(PositionMask);
}

Entity::Entity(Game* game)
{
   mGame = game;
   mNetFlags.set(Ghostable);
}

Entity::~Entity()
{
   //dtor
}

/** @brief performScopeQuery
  *
  * @todo: document this function
  */
void Entity::performScopeQuery(GhostConnection* connection)
{
   int i;
   for(i = 0; i < mGame->getEntities()->size(); i++) {
      connection->objectInScope((NetObject*) (mGame->getEntities()->operator[](i)));
   }
}

/** @brief setControlled
  *
  * @todo: document this function
  */
void Entity::setControlled(bool controlled)
{
   mIsControlled = controlled;
}

/** @brief isControlled
  *
  * @todo: document this function
  */
bool Entity::isControlled()
{
   return mIsControlled;
}



void Entity::setPos(const Vec2& pos)
{
   mPos = pos;
}

void Entity::setPos(float x, float y)
{
   mPos.set(x, y);
}

/** @brief modPos
  *
  * @todo: document this function
  */
void Entity::modPos(const Vec2& pos)
{
   mPos.x += pos.x;
   mPos.y += pos.y;
}

/** @brief getPos
  *
  * @todo: document this function
  */
const Vec2& Entity::getPos()
{
   return mPos;
}

/** @brief returns true if the other entity accurately reflects this entity's state
  */
bool Entity::isConsistentWith(const Entity& entity)
{
   return mPos == entity.mPos && mRot == entity.mRot;
}

U32 Entity::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream)
{
   // TODO assert that this is never called from the server side
   if(bitStream->writeFlag(updateMask & PositionMask)) {
      bitStream->writeFloat(mPos.x, 16);
      bitStream->writeFloat(mPos.y, 16);
   }

   if(bitStream->writeFlag(updateMask & RotationMask)) {
      bitStream->writeFloat(mRot.x, 16);
      bitStream->writeFloat(mRot.y, 16);
   }
}

void Entity::unpackUpdate(GhostConnection* connection, BitStream* bitStream)
{
   // position update
   if(bitStream->readFlag()) {
      mPos.x = bitStream->readFloat(16);
      mPos.y = bitStream->readFloat(16);
   }

   // rotation update
   if(bitStream->readFlag()) {
      mRot.x = bitStream->readFloat(16);
      mRot.y = bitStream->readFloat(16);
   }
}

bool Entity::onGhostAdd(GhostConnection* connection) {
   // set our game pointer. we can safely cast to GameConnection inside of Entities
   mGame = static_cast<GameInterface*>(connection->getInterface())->getGame();
   mGame->addEntity(this);
   return true;
}

/** @brief setRot
  *
  * @todo: document this function
  */
void Entity::setRot(const Vec2& rot)
{
   mRot = rot;
}

/** @brief getRot
  *
  * @todo: document this function
  */
const Vec2& Entity::getRot()
{
   return mRot;
}


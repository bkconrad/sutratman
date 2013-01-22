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

/** @brief packUpdate
  *
  * @todo: document this function
  */
U32 Entity::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream)
{

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
   Log::p("%d objects in scope", i);
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

void Entity::unpackUpdate(GhostConnection* c, BitStream* b) { }
bool Entity::onGhostAdd(GhostConnection* c) { mGame->addEntity(this); return true; }

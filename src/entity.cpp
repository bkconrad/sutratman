#include "entity.h"
#include "game.h"
#include "game_interface.h"
#include "log.h"

#include <tnlBitStream.h>

int Entity::IdIndex = 1;

TNL_IMPLEMENT_NETOBJECT(Entity);

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
   if(bitStream->writeFlag(updateMask & InitialMask)) {
      bitStream->writeFlag(connection->getScopeObject() == this);
   }

   if(bitStream->writeFlag(updateMask & PositionMask)) {
      bitStream->writeFloat(mPos.x, 16);
      bitStream->writeFloat(mPos.y, 16);
   }
}

/** @brief performScopeQuery
  *
  * @todo: document this function
  */
void Entity::performScopeQuery(GhostConnection* connection)
{
   for(int i = 0; i < mGame->getEntities()->size(); i++) {
      connection->objectInScope((NetObject*) (mGame->getEntities()->operator[](i)));
   }
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

/** @brief setGame
  *
  * @todo: document this function
  */
void Entity::setGame(Game* game)
{
   mGame = game;
}

void Entity::unpackUpdate(GhostConnection* c, BitStream* b) { }
bool Entity::onGhostAdd(GhostConnection* c) { return true; }

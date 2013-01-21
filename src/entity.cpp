#include "entity.h"
#include "game.h"
#include "game_interface.h"
#include "log.h"

#include <tnlBitStream.h>

TNL_IMPLEMENT_NETOBJECT(Entity);

Entity::Entity(Game* game)
{
   mGame = game;
   mNetFlags.set(Ghostable);
}

Entity::Entity() {
}

Entity::~Entity()
{
   //dtor
}

/** @brief unpackUpdate
  *
  * @todo: document this function
  */
void Entity::unpackUpdate(GhostConnection* connection, BitStream* bitStream)
{
   if(bitStream->readFlag()) {
      mPos.x = bitStream->readFloat(16);
      mPos.y = bitStream->readFloat(16);
   }
}

/** @brief packUpdate
  *
  * @todo: document this function
  */
U32 Entity::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream)
{
   if(bitStream->writeFlag(updateMask)) {
      bitStream->writeFloat(mPos.x, 16);
      bitStream->writeFloat(mPos.y, 16);
   }
}

/** @brief onGhostAdd
  *
  * @todo: document this function
  */
bool Entity::onGhostAdd(GhostConnection* connection)
{
   mGame = ((GameInterface* ) connection->getInterface())->getGame();
   mGame->addEntity(this);
   return true;
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

void Entity::setPos(Vec2& pos)
{
   mPos = pos;
}

void Entity::setPos(float x, float y)
{
   mPos.set(x, y);
}



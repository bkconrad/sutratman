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

/** @brief unpackUpdate
  *
  * @todo: document this function
  */
void Entity::unpackUpdate(GhostConnection* connection, BitStream* bitStream)
{
   // initial update
   if (bitStream->readFlag()) {
      // set our game pointer. we can safely cast to GameConnection inside of Entities
      mGame = static_cast<GameInterface*>(connection->getInterface())->getGame();

      // is controlled entity
      mIsControlled = bitStream->readFlag();
      if(mIsControlled) {
         // tell the game that this is our entity
         mGame->setControlEntity(this);
      }
   }

   // position update
   if(bitStream->readFlag()) {
      mPos.x = bitStream->readFloat(16);
      mPos.y = bitStream->readFloat(16);
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

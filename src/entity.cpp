#include "entity.h"
#include "game.h"
#include "log.h"

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

/** @brief onGhostAdd
  *
  * @todo: document this function
  */
bool Entity::onGhostAdd(GhostConnection* connection)
{
   Log::p("Ghost added!");
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

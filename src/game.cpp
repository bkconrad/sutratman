#include "game.h"
#include "log.h"
#include "entity.h"

using namespace TNL;

Game::Game(bool server)
{
   mServer = server;
   Game();
   setMsgTypes(LogNetConnection | LogFatalError | LogError | LogWarning);
}

Game::Game()
{
}

Game::~Game()
{
   for(int i; i < mEntities.size(); i++) {
      delete mEntities[i];
   }
}

void Game::addEntity(Entity* entity)
{
   mEntities.push_back(entity);
}

/** @brief getEntities
  *
  * @todo: document this function
  */
Vector<SafePtr<Entity> >* Game::getEntities()
{
   return &mEntities;
}


/** @brief writeString
  *
  * @todo: document this function
  */
void Game::writeString(const char* s)
{
   Log::p(s);
}


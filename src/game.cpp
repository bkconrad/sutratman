#include "game.h"
#include "entity.h"

Game::Game(bool server)
{
   mServer = server;
   Game();
}

Game::Game()
{
   if(mServer) {
      for (int i = 0; i < 20; i++) {
         addEntity(new Entity(this));
      }
   }
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

void Game::setControlEntity(Entity* entity) {
   // do nothing
   // TODO: assert that this is not called on the server side
}

/** @brief getEntities
  *
  * @todo: document this function
  */
Vector<Entity*>* Game::getEntities()
{
   return &mEntities;
}

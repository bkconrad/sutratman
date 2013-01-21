#include "entity.h"
#include "client/client_game.h"
#include "client/video.h"

ClientGame::ClientGame(Video* video)
{
   mVideo = video;
}

ClientGame::~ClientGame()
{
   //dtor
}

/** @brief addEntity
  *
  * @todo: document this function
  */
void ClientGame::addEntity(Entity* entity)
{
   Parent::addEntity(entity);
   if(mVideo) {
      mVideo->addEntity(entity);
   }
}


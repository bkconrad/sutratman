#include "log.h"
#include "player.h"
#include "client/client_game.h"
#include "client/video.h"

ClientGame::ClientGame(Video* video)
   : mVideo(video), mClientEntity(NULL)
{
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
   if (entity->mIsControlled) {
      mClientEntity = entity;
   }

   if(mVideo) {
      mVideo->addEntity(entity);
   }
}

/** @brief handleEvent
  *
  * @todo: document this function
  */
bool ClientGame::handleEvent(const irr::SEvent& event)
{
   if(!mClientEntity.isNull() && event.EventType == irr::EET_KEY_INPUT_EVENT) {
      static_cast<Player*>(mClientEntity.getPointer())->c2sMove();
   }
   return true;
}

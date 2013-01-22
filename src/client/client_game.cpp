#include "log.h"
#include "entity.h"
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
   if(mClientEntity) {
      mClientEntity->modPos(Vec2(1.0, 1.0));
      Log::p("key event handled");
   }
}

/** @brief setControlEntity
  *
  * @todo: document this function
  */
void ClientGame::setControlEntity(Entity* ent)
{
   mClientEntity = ent;
}

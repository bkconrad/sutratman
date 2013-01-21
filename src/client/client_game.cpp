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

   // TODO: add logic for figuring out which entity we control
   // for now, it's just the first one we get
   mClientEntity = mClientEntity ? mClientEntity : entity;

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

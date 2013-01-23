#include "log.h"
#include "player.h"
#include "client/client_game.h"
#include "client/video.h"

float ClientGame::MOUSESPEED = .001;

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
   if (entity->isControlled()) {
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
   static Vec2 lastPos(0.0, 0.0);

   if(!mClientEntity.isNull()) {
      switch (event.EventType)
      {
         case irr::EET_KEY_INPUT_EVENT:
            // TODO convert rotation in a move angle
            static_cast<Player*>(mClientEntity.getPointer())->c2sMove(mClientEntity->getRot().x);
         break;

         case irr::EET_MOUSE_INPUT_EVENT:
            Vec2 delta = lastPos - Vec2(event.MouseInput.X, event.MouseInput.Y);
            lastPos.set(event.MouseInput.X, event.MouseInput.Y);
            mClientEntity->modRot(Vec2(delta.x * ClientGame::MOUSESPEED, delta.y * ClientGame::MOUSESPEED));
            static_cast<Player*>(mClientEntity.getPointer())->c2sRotate(mClientEntity->getRot().x);
         break;
      }
   }
   return true;
}

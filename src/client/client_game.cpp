#include "log.h"
#include "player.h"
#include "client/client_game.h"
#include "client/input.h"
#include "client/video.h"

float ClientGame::MOUSESPEED = .1;

ClientGame::ClientGame()
   : mClientEntity(NULL)
{
   Input::get()->addListener(this);
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
   Video::get()->addEntity(entity);
}

/** @brief handleEvent
  *
  * @todo: document this function
  */
bool ClientGame::handle(const irr::SEvent& event)
{
   if(!mClientEntity.isNull()) {
      switch (event.EventType)
      {
         case irr::EET_KEY_INPUT_EVENT:
            // TODO convert rotation in a move angle
            static_cast<Player*>(mClientEntity.getPointer())->c2sMove(mClientEntity->getRot().x);
         break;

         case irr::EET_MOUSE_INPUT_EVENT:
            vec2 delta = Input::get()->getDelta();
            mClientEntity->modRot(vec2(0.0, delta.x * ClientGame::MOUSESPEED));
            static_cast<Player*>(mClientEntity.getPointer())->c2sRotate(mClientEntity->getRot().y);
         break;
      }
   }
   return true;
}

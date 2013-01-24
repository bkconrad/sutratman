#include "log.h"
#include "player.h"
#include "client/client_game.h"
#include "client/input.h"
#include "client/video.h"

float ClientGame::MOUSESPEED = .005;

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
            switch (event.KeyInput.Key) {
                case irr::KEY_KEY_W:
                    static_cast<Player*>(mClientEntity.getPointer())->c2sMove(mClientEntity->getRot().y);
                break;

                default:
                    return false;
                break;
            }
         break;

         case irr::EET_MOUSE_INPUT_EVENT:
            vec2 delta = Input::get()->getDelta();
            mClientEntity->modRot(vec3(0.0, delta.x * ClientGame::MOUSESPEED, 0.0));
            static_cast<Player*>(mClientEntity.getPointer())->c2sRotate(mClientEntity->getRot().y);
         break;
      }
   }
   return true;
}

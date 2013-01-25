#include "client/client_game.h"
#include "client/input.h"
#include "client/video.h"
#include "log.h"
#include "player.h"

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

/**
 * @brief add an entity to the game and video system
 */
void ClientGame::addEntity(Entity *entity)
{
    Parent::addEntity(entity);

    if(entity->isControlled())
    {
        mClientEntity = entity;
    }

    Video::get()->addEntity(entity);
}

bool ClientGame::handle(const irr::SEvent &event)
{
    if(!mClientEntity.isNull())
    {
        switch(event.EventType)
        {
        case irr::EET_KEY_INPUT_EVENT:

            switch(event.KeyInput.Key)
            {
            case irr::KEY_KEY_W:
                static_cast<Player*>(mClientEntity.getPointer())->c2sMove(mClientEntity->getRot().y);
                return true;
                break;

            default:
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

    return false;
}

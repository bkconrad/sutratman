#include "client/client_game.h"
#include "client/gui.h"
#include "client/input.h"
#include "diagnostics.h"
#include "log.h"
#include "mathutil.h"
#include "player.h"

using namespace mathutil;

using irr::core::vector3df;
using irr::core::vector2df;

float ClientGame::MOUSESPEED = .0005;
const float ClientGame::CAMERA_ACCELERATION = 0.01;
const float ClientGame::CAMERA_MAX_SPEED = 1.0;

ClientGame::ClientGame()
    : mClientEntity(NULL), mCameraRotation(0)
{
    Input::get()->addListener(this);
}

ClientGame::~ClientGame()
{
    mDevice->drop();
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
}

/** @brief initialize
  *
  * @todo: document this function
  */
void ClientGame::initialize()
{
    Parent::initialize();

    // window setup
    mDevice->setWindowCaption(L"Sutratman");

    // starting camera position
    mCameraRotation = 0.0;
    mCameraVelocity = 0.0;
    mCamera = mSceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 3, 5), irr::core::vector3df(0, 5, 0));
    mCamera->setNearValue(0.01f);

    irr::gui::IGUIEnvironment *guiEnv = mDevice->getGUIEnvironment();
    Gui::get()->init(guiEnv);
}

/** @brief update
  *
  * @todo: document this function
  */
void ClientGame::update(U32 t)
{
    Parent::update(t);

    // center on the focus entity if we have one
    if(mClientEntity.isValid())
    {
        vector3df pos = mClientEntity->getPos();
        vector3df rot = mClientEntity->getRot();

        DIAG(position, pos);
        DIAG(rotation, rot);

        float positiveAngularDistance = abs(rot.Y - mCameraRotation);
        float negativeAngularDistance = abs(mCameraRotation - rot.Y);
        float minimumAngularDistance = min(positiveAngularDistance, negativeAngularDistance);

        if(minimumAngularDistance > 5.0)
        {
            mCameraVelocity += positiveAngularDistance > negativeAngularDistance ? -CAMERA_ACCELERATION : CAMERA_ACCELERATION;
            mCameraVelocity = clamp(mCameraVelocity, -CAMERA_MAX_SPEED, CAMERA_MAX_SPEED);
            mCameraRotation += mCameraVelocity;
            mCameraRotation = fmod(mCameraRotation, DEGREES);
        }
        else
        {
            mCameraVelocity = 0.0;
        }

        vector2df cameraOffset(sin(degreesToRadians(mCameraRotation)), cos(degreesToRadians(mCameraRotation)));
        cameraOffset *= 0.02;

        mCamera->setTarget(irr::core::vector3df(pos.X, pos.Y + 0.01, pos.Z));
        mCamera->bindTargetAndRotation(true);
        mCamera->setPosition(irr::core::vector3df(pos.X + cameraOffset.X, pos.Y + 0.02, pos.Z + cameraOffset.Y));
    }
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
                static_cast<Player*>(mClientEntity.getPointer())->c2sMove(mClientEntity->getRot().Y);
                return true;
                break;

            default:
                break;
            }

            break;

        case irr::EET_MOUSE_INPUT_EVENT:
            vec2 delta = Input::get()->getDelta();
            mClientEntity->modRot(vector3df(0.0, delta.x * MOUSESPEED, 0.0));
            static_cast<Player*>(mClientEntity.getPointer())->c2sRotate(mClientEntity->getRot().Y / DEGREES);
            break;
        }
    }

    return false;
}

#include "client/client_game.h"
#include "client/gui.h"
#include "client/input.h"
#include "diagnostics.h"
#include "log.h"
#include "mathutil.h"
#include "player.h"

#include <cmath>

using namespace mathutil;

using irr::core::vector3df;
using irr::core::vector2df;

using std::min;
using std::max;

float ClientGame::MOUSESPEED = 1.0;
const float ClientGame::CAMERA_ACCELERATION = 20.0;
const float ClientGame::CAMERA_MAX_SPEED = 100.0;

ClientGame::ClientGame()
    : mClientEntity(NULL), mCameraRotation(0)
{
    Input::get()->addListener(this);
    irr::video::E_DRIVER_TYPE DriverTypes[] = {
        irr::video::EDT_DIRECT3D9,
        irr::video::EDT_DIRECT3D8,
        irr::video::EDT_OPENGL,
        irr::video::EDT_SOFTWARE
    };
    int i;
    for (i = 0; i < sizeof(DriverTypes) / sizeof(DriverTypes[0]); i++) {
        if (mDevice->isDriverSupported(DriverTypes[i])) {
            break;
        }
    }

    mDriverType = DriverTypes[i];
}

ClientGame::ClientGame(Game*)
{
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
        mClientEntity = static_cast<Player*>(entity);
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
void ClientGame::update()
{
    Parent::update();

    // center on the focus entity if we have one
    if(mClientEntity.isValid())
    {
        vector3df pos = mClientEntity->getPos();
        vector3df rot = mClientEntity->getRot();

        DIAG(position, pos);
        DIAG(rotation, rot);

        float angularDistance = fmod(rot.Y - mCameraRotation, 360.0);
                
        DIAG(angdis, angularDistance);
        if(angularDistance > 3.0) {
           // interval in seconds
           float interval = (TNL::Platform::getRealMilliseconds() - mLastFrameTime) * 0.001f;
           
           // determine the best direction to turn
           // (D>0) XOR (ABS(D)>180.0)
           bool direction = (angularDistance > 0) != (abs(angularDistance) > 180.0);
           
           float acceleration = direction ?  CAMERA_ACCELERATION : -CAMERA_ACCELERATION;
               
            acceleration *= interval;
            mCameraVelocity += acceleration;
            mCameraVelocity = max(min(mCameraVelocity, CAMERA_MAX_SPEED), -CAMERA_MAX_SPEED);

            mCameraRotation += mCameraVelocity * interval;
            mCameraRotation = fmod(mCameraRotation, DEGREES);
        } else {
            mCameraVelocity *= .1;
        }
        vector2df cameraOffset(sin(degreesToRadians(mCameraRotation)), cos(degreesToRadians(mCameraRotation)));
        cameraOffset *= 0.02;

        mCamera->setTarget(irr::core::vector3df(pos.X, pos.Y + 0.01, pos.Z));
        mCamera->bindTargetAndRotation(true);
        mCamera->setPosition(irr::core::vector3df(pos.X + cameraOffset.X, pos.Y + 0.02, pos.Z + cameraOffset.Y));
    }
}
/** @brief draw
  *
  * @todo: document this function
  */
void ClientGame::draw()
{
    Parent::draw();
    Gui::get()->draw();
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
                mClientEntity->c2sMove(mClientEntity->getRot().Y / DEGREES);
                return true;
                break;

            default:
                break;
            }

            break;

        case irr::EET_MOUSE_INPUT_EVENT:
            vector2df delta = Input::get()->getDelta();
            mClientEntity->modRot(vector3df(0.0, delta.X * MOUSESPEED, 0.0));
            mClientEntity->c2sRotate(mClientEntity->getRot().Y / DEGREES);
            break;
        }
    }

    return false;
}

#ifndef CLIENT_GAME_H_
#define CLIENT_GAME_H_

#include "client/listenerinterface.h"
#include "game.h"
#include "player.h"

#include <irrlicht.h>
#include <tnlGhostConnection.h>

class Video;
class Entity;

/**
 * @brief Class representing the game state, with additional overrides for
 * client-specific behavior
 */
class ClientGame : public Game, public ListenerInterface
{
    typedef Game Parent;
public:
    static float MOUSESPEED;
    static const float CAMERA_ACCELERATION; // acceleration of camera movement
    static const float CAMERA_MAX_SPEED; // max speed of camera movement

    ClientGame();
    ClientGame(Game*);
    virtual ~ClientGame();

    // overrides
    bool handle(const irr::SEvent &event);
    virtual void addEntity(Entity *entity);
    virtual void draw();
    virtual void update();
    virtual void initialize();

private:
    SafePtr<Player> mClientEntity;
    irr::scene::ICameraSceneNode *mCamera;
    irr::scene::ISceneNode *mSelectedSceneNode;
    float mCameraRotation;
    float mCameraVelocity;
    irr::scene::ILightSceneNode *mLight;
};

#endif /* CLIENT_GAME_H_ */
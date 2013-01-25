#ifndef CLIENT_GAME_H_
#define CLIENT_GAME_H_

#include "client/listenerinterface.h"
#include "game.h"

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

    ClientGame();
    virtual ~ClientGame();
    virtual void addEntity(Entity *entity);

    // overrides
    bool handle(const irr::SEvent &event);

private:
    SafePtr<Entity> mClientEntity;
};

#endif /* CLIENT_GAME_H_ */

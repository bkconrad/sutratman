#include "game.h"
#include "game_connection.h"
#include "game_interface.h"
#include "log.h"
#include "player.h"

#include <iostream>

using namespace TNL;
using namespace std;

TNL_IMPLEMENT_NETCONNECTION(GameConnection, NetClassGroupGame, true);

void GameConnection::onConnectionEstablished()
{
    Parent::onConnectionEstablished();

    if(isInitiator())
    {
        setGhostFrom(false);
        setGhostTo(true);
        Log::p("Connected to %s", getNetAddressString());
    }
    else
    {
        // create the new player
        Game *game = ((GameInterface*) getInterface())->getGame();
        SafePtr<Entity> entity = new Player(game);
        entity->setPos(TNL::Random::readF(), 0.0, TNL::Random::readF());
        game->addEntity(entity);
        setScopeObject(entity);
        setGhostFrom(true);
        setGhostTo(false);
        activateGhosting();
        Log::p("Connection from %s", getNetAddressString());
    }
}

void GameConnection::onConnectTerminated(NetConnection::TerminationReason reason, const char *str)
{
    Log::p("Connection attempt terminated: %s", str);
}

void GameConnection::onConnectionTerminated(NetConnection::TerminationReason reason, const char *str)
{
    Log::p("Connection closed: %s", str);
}

bool GameConnection::isDataToTransmit()
{
    return true;
}

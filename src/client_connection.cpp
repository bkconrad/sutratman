#include "client_connection.h"
#include "entity.h"
#include "game.h"
#include "game_interface.h"
#include "log.h"

#include <iostream>

using namespace TNL;
using namespace std;

TNL_IMPLEMENT_NETCONNECTION(ClientConnection, NetClassGroupGame, true);

void ClientConnection::onConnectionEstablished()
{
   Parent::onConnectionEstablished();
   if(isInitiator()) {
      setGhostFrom(false);
      setGhostTo(true);
      Log::p("Connected to %s", getNetAddressString());
   } else {
      // create the new player
      Game* game = ((GameInterface*) getInterface())->getGame();
      Entity* entity = new Entity(game);
      entity->setPos(TNL::Random::readF() * 10.0, TNL::Random::readF() * 10.0);
      game->addEntity(entity);
      setScopeObject(entity);
      setGhostFrom(true);
      setGhostTo(false);
      activateGhosting();
      Log::p("Connection from %s", getNetAddressString());
   }
}

TNL_IMPLEMENT_RPC(ClientConnection, s2cPlayerJoined, (), (),
NetClassGroupGameMask, RPCGuaranteedOrdered, RPCDirServerToClient, 0) {
   Log::p("Player joined!");
}

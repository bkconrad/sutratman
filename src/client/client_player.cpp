#include "player.h"
#include "game_interface.h"
#include "game.h"
#include "client/client_game.h"

#include <tnlBitStream.h>

using namespace TNL;

void Player::unpackUpdate(GhostConnection* connection, BitStream* bitStream) {
   Parent::unpackUpdate(connection, bitStream);

   // initial update
   if (bitStream->readFlag()) {
      // set our game pointer. we can safely cast to GameConnection inside of Entities
      mGame = static_cast<GameInterface*>(connection->getInterface())->getGame();
      // we can also safely cast our game to a client game
      mClientGame = static_cast<ClientGame*>(mGame);
   }

   // is controlled entity
   mIsControlled = bitStream->readFlag();

}

bool Player::onGhostAdd(GhostConnection* connection) {
   return Parent::onGhostAdd(connection);
}

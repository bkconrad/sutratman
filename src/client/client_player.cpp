#include "player.h"
#include "game_interface.h"
#include "game.h"
#include "client/client_game.h"

#include <tnlBitStream.h>

using namespace TNL;

void Player::unpackUpdate(GhostConnection* connection, BitStream* bitStream) {
   // initial update
   if (bitStream->readFlag()) {
      // set our game pointer. we can safely cast to GameConnection inside of Entities
      mGame = static_cast<GameInterface*>(connection->getInterface())->getGame();
      // we can also safely cast our game to a client game
      mClientGame = static_cast<ClientGame*>(mGame);
   }

   // is controlled entity
   mIsControlled = bitStream->readFlag();

   // position update
   if(bitStream->readFlag()) {
      mPos.x = bitStream->readFloat(16);
      mPos.y = bitStream->readFloat(16);
   }
}

bool Player::onGhostAdd(GhostConnection* connection) {
   return Parent::onGhostAdd(connection);
}

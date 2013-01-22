#include "player.h"
#include "log.h"

SUT_IMPLEMENT_GAME_ENTITY(Player);

U32 Player::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream) {

   if(bitStream->writeFlag(updateMask & InitialMask)) {
   }

   Log::p("%s scope object", bitStream->writeFlag(connection->getScopeObject() == this) ? "" : "not");

   if(bitStream->writeFlag(updateMask & PositionMask)) {
      bitStream->writeFloat(mPos.x, 16);
      bitStream->writeFloat(mPos.y, 16);
   }
   return 0;
}

Player::Player(Game* game)
{
   mGame = game;
}

Player::~Player()
{
   //dtor
}

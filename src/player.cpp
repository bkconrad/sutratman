#include "player.h"
#include "log.h"

SUT_IMPLEMENT_GAME_ENTITY(Player);

U32 Player::packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream)
{
   // remember to take the mask from the Parent
   updateMask = Parent::packUpdate(connection, updateMask, bitStream);
   if(bitStream->writeFlag(updateMask & InitialMask)) {
   }

   bitStream->writeFlag(connection->getScopeObject() == this);
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

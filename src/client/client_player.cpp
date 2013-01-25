#include "client/client_game.h"
#include "game.h"
#include "game_interface.h"
#include "player.h"

#include <tnlBitStream.h>

using namespace TNL;

void Player::unpackUpdate(GhostConnection *connection, BitStream *bitStream)
{
    Parent::unpackUpdate(connection, bitStream);

    // initial update
    if(bitStream->readFlag())
    {
    }

    // is controlled entity
    mIsControlled = bitStream->readFlag();

}

bool Player::onGhostAdd(GhostConnection *connection)
{
    // we can safely cast our game to a client game
    mClientGame = static_cast<ClientGame*>(mGame);
    return Parent::onGhostAdd(connection);
}

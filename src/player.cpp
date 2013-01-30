#include "client/client_game.h"
#include "game.h"
#include "log.h"
#include "player.h"
#include "mathutil.h"

using namespace mathutil;

TNL_IMPLEMENT_NETOBJECT(Player);

TNL_IMPLEMENT_NETOBJECT_RPC(Player, c2sMove, (F32 angle), (angle),
                            NetClassGroupAllMask,  RPCGuaranteedOrdered, RPCToGhostParent, 0)
{
    // TODO check client's ownership
    vector3df vel(-sin(angle * RADIANS), 0.0, -cos(angle * RADIANS));
    vel *= Entity::MOVESPEED;
    mVelocity = vel;
          
   mLastKnownPosition = getPos();
   moveTo(mLastKnownPosition + mVelocity);
    
    setMaskBits(VelocityMask);
    setMaskBits(PositionMask);
}

U32 Player::packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream)
{
    // remember to take the mask from the Parent
    updateMask = Parent::packUpdate(connection, updateMask, bitStream);
    
    bitStream->writeFlag(connection->getScopeObject() == this);
    return 0;
}


void Player::unpackUpdate(GhostConnection *connection, BitStream *bitStream)
{
    Parent::unpackUpdate(connection, bitStream);

    // is controlled entity
    mIsControlled = bitStream->readFlag();

}

Player::Player(Game *game)
{
    mGame = game;
}

Player::~Player()
{
    //dtor
}

bool Player::onGhostAdd(GhostConnection *connection)
{
    // we can safely cast our game to a client game
    mClientGame = new ClientGame(mGame);
    return Parent::onGhostAdd(connection);
}

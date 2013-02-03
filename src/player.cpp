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
   mCollisionAnimator->setVelocity(mVelocity);
   mState = Player::PS_WALK;
    
    setMaskBits(VelocityMask);
    setMaskBits(PositionMask);
}

TNL_IMPLEMENT_NETOBJECT_RPC(Player, c2sStop, (), (),
                            NetClassGroupAllMask,  RPCGuaranteedOrdered, RPCToGhostParent, 0)
{
   mLastKnownPosition = getPos();
   mVelocity = vector3df(0,0,0);
   mCollisionAnimator->setVelocity(mVelocity);
   mState = Player::PS_IDLE;
    
    setMaskBits(VelocityMask);
    setMaskBits(PositionMask);
}

U32 Player::packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream)
{
    // remember to take the mask from the Parent
    updateMask = Parent::packUpdate(connection, updateMask, bitStream);
    
    bitStream->writeFlag(connection->getScopeObject() == this);
    bitStream->writeInt(mState, 4);
    return 0;
}


void Player::unpackUpdate(GhostConnection *connection, BitStream *bitStream)
{
    Parent::unpackUpdate(connection, bitStream);

    // is controlled entity
    mIsControlled = bitStream->readFlag();
    setState((PlayerState) bitStream->readInt(4));

}

Player::Player(Game *game)
   : mState(PS_IDLE)
{
    mGame = game;
}

Player::~Player()
{
    //dtor
}

void Player::onGhostAddBeforeUpdate(GhostConnection *connection)
{
    // we can safely cast our game to a client game
    mClientGame = new ClientGame(mGame);
    return Parent::onGhostAddBeforeUpdate(connection);
}

void Player::setState(PlayerState state)
{
   mState = state;
   switch (mState) {
      case PS_IDLE:
         mNode->setFrameLoop(1, 210);
      break;
      
      case PS_WALK:
         mNode->setFrameLoop(395, 415);
      break;
   }
}

Player::PlayerState Player::getState()
{
   return mState;
}

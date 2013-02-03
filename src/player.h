#ifndef PLAYER_H_
#define PLAYER_H_

#include "mobile_entity.h"

#include <tnl.h>

using namespace TNL;

class Game;

class Player : public MobileEntity
{
public:
    enum PlayerState {
       PS_IDLE,
       PS_WALK,
       PS_ATTACK
    };
    
    TNL_DECLARE_CLASS(Player);
    TNL_DECLARE_RPC(c2sMove, (F32 angle));
    TNL_DECLARE_RPC(c2sStop, ());
    
    explicit Player(Game *game = NULL);
    virtual ~Player();
    virtual U32 packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream);
    void onGhostAddBeforeUpdate(GhostConnection* connection);
    void unpackUpdate(GhostConnection* connection, BitStream* bitStream);
    void setState(PlayerState state);
    PlayerState getState();

private:
    typedef MobileEntity Parent;
    PlayerState mState;
};

#endif /* PLAYER_H_ */

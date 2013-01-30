#ifndef PLAYER_H_
#define PLAYER_H_

#include "mobile_entity.h"

#include <tnl.h>

using namespace TNL;

class Game;

class Player : public MobileEntity
{
public:
    TNL_DECLARE_CLASS(Player);
    TNL_DECLARE_RPC(c2sMove, (F32 angle));
    
    explicit Player(Game *game = NULL);
    virtual ~Player();
    virtual U32 packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream);
    bool onGhostAdd(GhostConnection* connection);
    void unpackUpdate(GhostConnection* connection, BitStream* bitStream);

private:
    typedef MobileEntity Parent;
};

#endif /* PLAYER_H_ */

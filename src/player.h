#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"

#include <tnl.h>

using namespace TNL;

class Game;

class Player : public Entity
{
public:
    explicit Player(Game *game = NULL);
    virtual ~Player();
    virtual U32 packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream);
    bool onGhostAdd(GhostConnection* connection);
    void unpackUpdate(GhostConnection* connection, BitStream* bitStream);
    TNL_DECLARE_CLASS(Player);

private:
    typedef Entity Parent;
};

#endif /* PLAYER_H_ */

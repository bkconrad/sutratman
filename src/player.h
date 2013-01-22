#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <tnl.h>

using namespace TNL;

class Game;
class Player : public Entity
{
   public:
      explicit Player (Game* game = NULL);
      virtual ~Player();
      virtual U32 packUpdate(GhostConnection* connection, U32 updateMask, BitStream* bitStream);
      SUT_DECLARE_GAME_ENTITY(Player);
   protected:
   private:
      typedef Entity Parent;
};

#endif // PLAYER_H

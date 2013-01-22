#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Game;
class Player : public Entity
{
   public:
      explicit Player (Game* game = NULL);
      virtual ~Player();
      SUT_DECLARE_GAME_ENTITY(Player);
   protected:
   private:
};

#endif // PLAYER_H

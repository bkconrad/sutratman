#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <tnlNetInterface.h>

class Game;
class GameInterface: public TNL::NetInterface
{
   public:
      GameInterface(const TNL::Address& address, Game* game);
      virtual ~GameInterface();
      Game* getGame();
   protected:
   private:
      Game* mGame;
};

#endif // GAMEINTERFACE_H

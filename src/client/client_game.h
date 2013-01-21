#ifndef CLIENT_GAME_H_
#define CLIENT_GAME_H_

#include "game.h"

#include <tnlGhostConnection.h>

class Entity;
class Video;

/**
@brief Class representing the game state, with additional overrides
for client-specific behavior
*/
class ClientGame : public Game
{
   typedef Game Parent;
   public:
      ClientGame(Video* video= NULL);
      virtual ~ClientGame();
      virtual void addEntity(Entity* entity);
   protected:
   private:
      Video* mVideo;
};

#endif /* CLIENT_GAME_H_ */

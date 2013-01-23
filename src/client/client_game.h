#ifndef CLIENT_GAME_H_
#define CLIENT_GAME_H_

#include "game.h"

#include <tnlGhostConnection.h>
#include <irrlicht.h>

class Video;
class Entity;

/**
@brief Class representing the game state, with additional overrides
for client-specific behavior
*/
class ClientGame : public Game
{
   typedef Game Parent;
   public:
      static float MOUSESPEED;
      ClientGame(Video* video = NULL);
      virtual ~ClientGame();
      virtual void addEntity(Entity* entity);

      bool handleEvent(const irr::SEvent& event);

   protected:
   private:
      Video* mVideo;
      SafePtr<Entity> mClientEntity;
};

#endif /* CLIENT_GAME_H_ */

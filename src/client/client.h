#ifndef CLIENT_H_
#define CLIENT_H_

#include "client/video.h"
#include "game_connection.h"
#include <irrlicht.h>

#include <gtest/gtest_prod.h>

class GameInterface;
class ClientGame;
class Input;
class Client : public irr::IEventReceiver
{
   public:
      Client(Video* video = NULL, GameConnection* connection = NULL, ClientGame* game = NULL);
      void go();
      bool connect(char* host);
      bool init();
      virtual ~Client();

      // overrides
      bool OnEvent(const irr::SEvent& event);
   protected:
   private:
      Video* mVideo;
      Input* mInput;
      GameConnection* mConnection;
      RefPtr<GameInterface> mInterface;
      ClientGame *mGame;

      bool step();
      void serviceConnection();

      FRIEND_TEST(network, connectivity);
};

#endif /* CLIENT_H_ */

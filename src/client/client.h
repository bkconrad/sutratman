#ifndef CLIENT_H_
#define CLIENT_H_

#include "client/video.h"
#include "game_connection.h"
#include <irrlicht.h>

#include <gtest/gtest_prod.h>

class GameInterface;
class ClientGame;
class Input;
class Client
{
   public:
      Client(GameConnection* connection = NULL, ClientGame* game = NULL);
      void go();
      bool connect(char* host);
      bool init();
      virtual ~Client();

      void serviceConnection();
      bool step();

   protected:
   private:
      Input* mInput;
      GameConnection* mConnection;
      RefPtr<GameInterface> mInterface;
      ClientGame *mGame;

      FRIEND_TEST(network, connectivity);
};

#endif /* CLIENT_H_ */

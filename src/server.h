#ifndef SERVER_H
#define SERVER_H

#include "game_interface.h"

#include "tnl.h"
#include "tnlRPC.h"

#include "gtest/gtest_prod.h"

using namespace TNL;
using namespace std;

class Game;
class Server
{
   public:
      Server();
      virtual ~Server();
      void go();
      bool init();
      void host(const char* host, const char* port);
   protected:
   private:
      GameInterface *mInterface;
      Game *mGame;
      void serviceConnections();

   FRIEND_TEST(network, server);

};

#endif // SERVER_H

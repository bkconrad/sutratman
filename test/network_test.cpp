#include "client/client.h"
#include "server.h"
#include "game.h"
#include "gtest/gtest.h"

#include "tnl.h"
#include "tnlEventConnection.h"

#include <pthread.h>

using namespace TNL;

int serverStatus = 0;
int clientStatus = 0;

class TestConnection : public GameConnection {
public:
   typedef GameConnection Parent;
   int result;

   TestConnection() {
      result = 0;
   }

   virtual void onConnectTerminated(NetConnection::TerminationReason reason, const char* str)
   {
      if (isInitiator()) {
         clientStatus = -1;
      } else {
         serverStatus = -1;
      }
   }

   virtual void onConnectionEstablished()
   {
      if (isInitiator()) {
         clientStatus = 1;
      } else {
         serverStatus = 1;
      }
   }

   TNL_DECLARE_NETCONNECTION(TestConnection);
};

TNL_IMPLEMENT_NETCONNECTION(TestConnection, NetClassGroupGame, true);

// testing util function. args is a pointer to the server
void * connectToServer(void* args) {
   TestConnection *connection = new TestConnection;
   Client c(connection);
   c.connect((char*) "localhost:28000");
   U32 start = Platform::getRealMilliseconds();
   while(!serverStatus || !clientStatus) {
      c.serviceConnection();
      Platform::sleep(1);
   }

   pthread_exit(NULL);
   return NULL;
}

TEST(network, connectivity) {
   Server s;
   s.mGame = new Game();
   s.host("localhost", "28000");

   pthread_t thread;
   pthread_create(&thread, NULL, connectToServer, NULL);

   U32 start = Platform::getRealMilliseconds();
   while(!serverStatus || !clientStatus) {
      s.serviceConnections();
      Platform::sleep(1);
   }

   ASSERT_EQ(1, clientStatus);
   ASSERT_EQ(1, serverStatus);
}

#include "client/client.h"
#include "server.h"
#include "game.h"
#include "gtest/gtest.h"

#include "tnl.h"
#include "tnlEventConnection.h"

#include <pthread.h>

using namespace TNL;

class TestConnection : public GameConnection {
public:

   static int serverStatus;
   static int clientStatus;
   typedef GameConnection Parent;

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

int TestConnection::serverStatus = 0;
int TestConnection::clientStatus = 0;

TNL_IMPLEMENT_NETCONNECTION(TestConnection, NetClassGroupGame, true);

// testing util function
void * connectToServer(void* args) {
   TestConnection *connection = new TestConnection;
   Client c(connection);
   c.connect((char*) "localhost:28000");

   while(!TestConnection::serverStatus || !TestConnection::clientStatus) {
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
   while(!TestConnection::serverStatus || !TestConnection::clientStatus) {
      s.serviceConnections();
      Platform::sleep(1);
   }

   ASSERT_EQ(1, TestConnection::clientStatus);
   ASSERT_EQ(1, TestConnection::serverStatus);
}

TEST(network, loopback) {
   TestConnection::serverStatus = TestConnection::clientStatus = 0;
   
   Server s;
   
   TestConnection *connection = new TestConnection;
   Client c(connection);
   
   s.host("localhost", "28000");
   c.loopbackConnect(&s);
   while(!TestConnection::serverStatus || !TestConnection::clientStatus) {
      s.serviceConnections();
      c.serviceConnection();
      Platform::sleep(1);
   }

   ASSERT_EQ(1, TestConnection::clientStatus);
   ASSERT_EQ(1, TestConnection::serverStatus);
}

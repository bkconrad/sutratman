#include "client/client.h"
#include "server.h"
#include "game.h"
#include "log.h"
#include "gtest/gtest.h"

#include "tnl.h"
#include "tnlEventConnection.h"

#include <pthread.h>

using namespace TNL;

class TestConnection : public GameConnection {
public:

   static int serverStatus;
   static int clientStatus;
   static bool done;
   
   typedef GameConnection Parent;

   virtual void onConnectTerminated(NetConnection::TerminationReason reason, const char* str)
   {
      if (isInitiator()) {
         clientStatus = -1;
      } else {
         serverStatus = -1;
      }
      done = true;
      Log::p(str);
   }

   virtual void onConnectionEstablished()
   {
      GameConnection::onConnectionEstablished();
      
      if (isInitiator()) {
         clientStatus = 1;
      } else {
         serverStatus = 1;
      }
      if (clientStatus && serverStatus) {
         done = true;
      }
   }
   
   static void reset() {
      serverStatus = clientStatus = 0;
      done = false;
   }

   TNL_DECLARE_NETCONNECTION(TestConnection);
};

int TestConnection::serverStatus = 0;
int TestConnection::clientStatus = 0;
bool TestConnection::done = false;

TNL_IMPLEMENT_NETCONNECTION(TestConnection, NetClassGroupGame, true);

// testing util function
void * connectToServer(void* args) {
   TestConnection *connection = new TestConnection;
   Client c(connection);
   c.connect((char*) "localhost:28000");

   while(!TestConnection::done) {
      c.serviceConnection();
      Platform::sleep(1);
   }

   pthread_exit(NULL);
   return NULL;
}

TEST(network, connectivity) {
   TestConnection::reset();
   Server s;
   s.init();

   pthread_t thread;
   pthread_create(&thread, NULL, connectToServer, NULL);

   while(!TestConnection::done) {
      s.serviceConnections();
      Platform::sleep(1);
   }

   EXPECT_EQ(1, TestConnection::clientStatus);
   EXPECT_EQ(1, TestConnection::serverStatus);
}

TEST(network, loopback) {
   TestConnection::reset();
   
   Server s;
   s.init();
   
   TestConnection *connection = new TestConnection;
   Client c(connection);

   c.loopbackConnect(&s);
   while(!TestConnection::done) {
      s.serviceConnections();
      c.serviceConnection();
      Platform::sleep(1);
   }

   EXPECT_EQ(1, TestConnection::clientStatus);
   EXPECT_EQ(1, TestConnection::serverStatus);
}

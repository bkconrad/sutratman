#include "client/client.h"
#include "server.h"
#include "game.h"
#include "gtest/gtest.h"

#include "tnl.h"
#include "tnlEventConnection.h"

#include <unistd.h>

using namespace TNL;

class TestConnection : public GameConnection {
public:
   typedef GameConnection Parent;
   static int result;
   TestConnection() {
      result = 0;
   }
   virtual void onConnectTerminated(NetConnection::TerminationReason reason, const char* str) { result = -1; }
   virtual void onConnectionTerminated() { result = -1; }
   virtual void onConnectionEstablished() { result = 1; }

   TNL_DECLARE_NETCONNECTION(TestConnection);
};

int TestConnection::result = 0;

TNL_IMPLEMENT_NETCONNECTION(TestConnection, NetClassGroupGame, true);

TEST(network, connectivity) {
   int pid = fork();
   TestConnection *connection = new TestConnection;

   if (pid) {
      Server s;
      s.mGame = new Game();
      s.host("localhost", "28000");
      U32 start = Platform::getRealMilliseconds();
      while(TestConnection::result == 0 && Platform::getRealMilliseconds() - start < 10000) {
         s.serviceConnections();
         Platform::sleep(1);
      }
      ASSERT_TRUE(connection->result == 1);
      exit(0);
   } else {
      Client c(connection);
      c.connect((char*) "localhost:28000");
      U32 start = Platform::getRealMilliseconds();
      while(TestConnection::result == 0 && Platform::getRealMilliseconds() - start < 10000) {
         c.step();
         Platform::sleep(1);
      }
      ASSERT_TRUE(connection->result == 1);
   }
}

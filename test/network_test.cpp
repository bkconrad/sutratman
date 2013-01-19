#include "client/client.h"
#include "server.h"
#include "gtest/gtest.h"

#include "tnl.h"
#include "tnlEventConnection.h"

#include <unistd.h>

using namespace TNL;

class TestConnection : public EventConnection {
public:
   typedef EventConnection Parent;
   int result;
   TestConnection() {
      result = 0;
   }
   void onConnectTerminated() { result = -1; }
   void onConnectionEstablished() { result = 1; }

   TNL_DECLARE_NETCONNECTION(TestConnection);
};

TNL_IMPLEMENT_NETCONNECTION(TestConnection, NetClassGroupGame, true);

TEST(network, server) {
   int pid = fork();

   if (!pid) {
      Server s;
      s.host("localhost", "28000");
      for (int i = 0; i < 1000; i++) {
         s.serviceConnections();
         Platform::sleep(10);
      }
      exit(0);
   } else {
      Address foreignAddress("localhost:28000");
      Address bindAddress(IPProtocol, Address::Any, 0);
      NetInterface *interface = new NetInterface(bindAddress);
      TestConnection *connection = new TestConnection;
      connection->connect(interface, foreignAddress);
      while(connection->result == 0) {
         interface->checkIncomingPackets();
         interface->processConnections();
         Platform::sleep(10);
      }
      ASSERT_TRUE(connection->result == 1);
   }
}

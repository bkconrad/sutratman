#ifndef SERVER_H
#define SERVER_H

#include "tnl.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

#include "gtest/gtest_prod.h"

using namespace TNL;
using namespace std;

class Server
{
   public:
      Server();
      virtual ~Server();
      void go();
      void host(const char* host, const char* port);
   protected:
   private:
      NetInterface *mInterface;
      void serviceConnections();

   FRIEND_TEST(network, server);

};

#endif // SERVER_H

#ifndef SERVER_H
#define SERVER_H

#include "tnl.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

using namespace TNL;
using namespace std;

class Server
{
   public:
      Server();
      virtual ~Server();
      void go();
   protected:
   private:
      NetInterface *mInterface;
      void serviceConnections();

};

#endif // SERVER_H

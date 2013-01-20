#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "tnl.h"
#include "tnlNetConnection.h"
#include "tnlGhostConnection.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

using namespace TNL;
using namespace std;

class ClientConnection : public GhostConnection {
   typedef GhostConnection Parent;
   public:
      void onConnectionEstablished();
      TNL_DECLARE_NETCONNECTION(ClientConnection);
      TNL_DECLARE_RPC(s2cPlayerJoined, ());
};

#endif // CLIENT_CONNECTION_H

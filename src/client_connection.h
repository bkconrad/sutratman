#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "tnl.h"
#include "tnlNetConnection.h"
#include "tnlEventConnection.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

using namespace TNL;
using namespace std;

class ClientConnection : public EventConnection {
   typedef EventConnection Parent;
   public:
      TNL_DECLARE_NETCONNECTION(ClientConnection);

      TNL_DECLARE_RPC(c2sHandshake, ());
      TNL_DECLARE_RPC(s2cHandshake, ());
};

#endif // CLIENT_CONNECTION_H

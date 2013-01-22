#ifndef GAME_CONNECTION_H
#define GAME_CONNECTION_H

#include "tnl.h"
#include "tnlNetConnection.h"
#include "tnlGhostConnection.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

using namespace TNL;
using namespace std;

class GameConnection : public GhostConnection {
   typedef GhostConnection Parent;
   public:
      virtual void onConnectionEstablished();
      virtual void onConnectTerminated(NetConnection::TerminationReason reason, const char* str);
      virtual void onConnectionTerminated(NetConnection::TerminationReason reason, const char* str);
      virtual bool isDataToTransmit();
      TNL_DECLARE_NETCONNECTION(GameConnection);
      TNL_DECLARE_RPC(c2sIsAlive, ());
};

#endif // GAME_CONNECTION_H

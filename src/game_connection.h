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
      void onConnectionEstablished();
      TNL_DECLARE_NETCONNECTION(GameConnection);
      TNL_DECLARE_RPC(s2cPlayerJoined, ());
};

#endif // GAME_CONNECTION_H

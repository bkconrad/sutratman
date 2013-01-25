#ifndef GAME_CONNECTION_H_
#define GAME_CONNECTION_H_

#include "tnl.h"
#include "tnlGhostConnection.h"
#include "tnlNetConnection.h"
#include "tnlNetInterface.h"
#include "tnlRPC.h"

using namespace TNL;
using namespace std;

class GameConnection : public GhostConnection
{
    typedef GhostConnection Parent;
public:
    virtual bool isDataToTransmit();
    virtual void onConnectionEstablished();
    virtual void onConnectionTerminated(NetConnection::TerminationReason reason, const char *str);
    virtual void onConnectTerminated(NetConnection::TerminationReason reason, const char *str);
    TNL_DECLARE_NETCONNECTION(GameConnection);
};

#endif /* GAME_CONNECTION_H_ */

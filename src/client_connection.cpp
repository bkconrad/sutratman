#include "client_connection.h"
#include "log.h"

#include <iostream>

using namespace TNL;
using namespace std;

TNL_IMPLEMENT_NETCONNECTION(ClientConnection, NetClassGroupGame, true);

void ClientConnection::onConnectionEstablished()
{
   Log::p("Connected successfully");
}

TNL_IMPLEMENT_RPC(ClientConnection, c2sHandshake, (), (),
NetClassGroupGameMask, RPCGuaranteedOrdered, RPCDirClientToServer, 0) {
   cout << "Client connected" << endl;
   s2cHandshake();
}

TNL_IMPLEMENT_RPC(ClientConnection, s2cHandshake, (), (),
   NetClassGroupGameMask, RPCGuaranteedOrdered, RPCDirServerToClient, 0) {
   cout << "Got server response" << endl;
}

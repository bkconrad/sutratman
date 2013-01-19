#include "client/client.h"
#include "log.h"

#include <tnl.h>
#include <tnlNetInterface.h>
#include <tnlRPC.h>

#include <iostream>

using namespace TNL;
using namespace std;

Client::Client()
{
   mVideo = NULL;
   mConnection = NULL;
}

Client::~Client()
{
   //dtor
}

/** @brief Main client entry point
  */
void Client::go()
{
   while (step()) {
      Platform::sleep(10);
   }
}


/** @brief Initialize all dependencies for the Client which are still missing
  */
bool Client::init()
{
   if(!mVideo) {
      mVideo = new Video;
   }
   connect((char *) "localhost:28000");
   return !!mVideo;
}


/** @brief step
  *
  * @todo: document this function
  */
bool Client::step()
{
   bool result = true;
   result = result && mVideo->run();
   serviceConnection();
   return result;
}


/** @brief connect
  *
  * @todo: document this function
  */
bool Client::connect(char* host)
{
   Address foreignAddress(host);
   Address bindAddress(IPProtocol, Address::Any, 0);
   mInterface = new NetInterface(bindAddress);
   mConnection = new ClientConnection;
   Log::p("Connecting");
   mConnection->connect(mInterface, foreignAddress);
   mConnection->c2sHandshake();
   return true;
}

/** @brief serviceConnection
  *
  * @todo: document this function
  */
void Client::serviceConnection()
{
   mInterface->checkIncomingPackets();
   mInterface->processConnections();
}


#include "client/client.h"
#include "log.h"
#include "client_game.h"
#include "game_interface.h"

#include <tnl.h>
#include <tnlRPC.h>

#include <iostream>

using namespace TNL;
using namespace std;

Client::Client(GameConnection* connection, ClientGame* game)
   : mConnection(connection), mGame(game)
{
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
      Platform::sleep(1);
   }
}


/** @brief Initialize all dependencies for the Client which are still missing
  */
bool Client::init()
{
   mVideo = Video::get();
   mGame = mGame ? mGame : new ClientGame();

   connect((char *) "localhost:28000");

   return !!mVideo;
}


/** @brief step
  *
  * @todo: document this function
  */
bool Client::step()
{
   serviceConnection();
   return mVideo ? mVideo->run() : true;
}


/** @brief connect
  *
  * @todo: document this function
  */
bool Client::connect(char* host)
{
   Address foreignAddress(host);
   Address bindAddress(IPProtocol, Address::Any, 0);
   mInterface = new GameInterface(bindAddress, mGame);
   mConnection = mConnection ? mConnection : new GameConnection;
   Log::p("Connecting");
   mConnection->connect(mInterface, foreignAddress);
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

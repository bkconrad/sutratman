#include "server.h"
#include "game.h"

using namespace TNL;
using namespace std;

Server::Server()
{
   mGame = NULL;
}

Server::~Server()
{
   //dtor
}

/** @brief init
  *
  * @todo: document this function
  */
bool Server::init()
{
   if(!mGame) {
      mGame = new Game(true);
   }

   host((const char *) "localhost", "28000");
   return true;
}

/** @brief go
  *
  * @todo: document this function
  */
void Server::go()
{
   while(true) {
      serviceConnections();
      Platform::sleep(1);
   }
}

/** @brief host
  *
  * @todo: document this function
  */
void Server::host(const char* host, const char* port)
{
   string hostPort(host);
   hostPort += ":";
   hostPort += port;
   Address address(hostPort.c_str());
   mInterface = new GameInterface(address, mGame);
   mInterface->setAllowsConnections(true);
}

/** @brief serviceConnections
  *
  * @todo: document this function
  */
void Server::serviceConnections()
{
   mInterface->checkIncomingPackets();
   mInterface->processConnections();
}


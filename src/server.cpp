#include "server.h"

using namespace TNL;
using namespace std;

Server::Server()
{
   //ctor
}

Server::~Server()
{
   //dtor
}

/** @brief go
  *
  * @todo: document this function
  */
void Server::go()
{
   Address address("127.0.0.1:28000");
   mInterface = new NetInterface(address);
   mInterface->setAllowsConnections(true);
   while(true) {
      serviceConnections();
      Platform::sleep(10);
   }
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


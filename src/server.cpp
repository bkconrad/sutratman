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
   host((const char *) "localhost", "28000");
   while(true) {
      serviceConnections();
      Platform::sleep(10);
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
   mInterface = new NetInterface(address);
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


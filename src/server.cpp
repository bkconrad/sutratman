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

/**
 * @brief create a new game and begin hosting
 */
bool Server::init()
{
    if(!mGame)
    {
        mGame = new Game(true);
    }
    mGame->initialize();

    host((const char *) "localhost", "28000");
    return true;
}

/**
 * @brief main server loop
 */
void Server::go()
{
    while(true)
    {
        serviceConnections();
        mGame->update();
        Platform::sleep(1);
    }
}

void Server::host(const char *host, const char *port)
{
    string hostPort(host);
    hostPort += ":";
    hostPort += port;
    Address address(hostPort.c_str());
    mInterface = new GameInterface(address, mGame);
    mInterface->setAllowsConnections(true);
}

/**
 * @brief perform network maintenance
 */
void Server::serviceConnections()
{
    mInterface->checkIncomingPackets();
    mInterface->processConnections();
}

NetInterface *Server::getInterface()
{
   return mInterface;
}
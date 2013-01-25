#include "client/client.h"
#include "client_game.h"
#include "game_interface.h"
#include "log.h"

#include <tnl.h>
#include <tnlRPC.h>

#include <iostream>

using namespace TNL;
using namespace std;

Client::Client(GameConnection *connection, ClientGame *game)
    : mConnection(connection), mGame(game)
{
}

Client::~Client()
{
    //dtor
}

/**
 * @brief Main client entry point
 */
void Client::go()
{
    while(step())
    {
        Platform::sleep(1);
    }
}


/**
 * @brief Initialize all dependencies for the Client which are still missing
 * and connect to a server
 */
bool Client::init()
{
    mGame = mGame ? mGame : new ClientGame();

    connect((char *) "localhost:28000");

    return true;
}

bool Client::step()
{
    serviceConnection();
    return Video::get()->run();
}

bool Client::connect(char *host)
{
    Address foreignAddress(host);
    Address bindAddress(IPProtocol, Address::Any, 0);
    mInterface = new GameInterface(bindAddress, mGame);
    mConnection = mConnection ? mConnection : new GameConnection;
    Log::p("Connecting");
    mConnection->connect(mInterface, foreignAddress);
    return true;
}

void Client::serviceConnection()
{
    mInterface->checkIncomingPackets();
    mInterface->processConnections();
}

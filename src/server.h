#ifndef SERVER_H_
#define SERVER_H_

#include "game_interface.h"

#include <tnl.h>
#include <tnlRPC.h>

#include <gtest/gtest_prod.h>

using namespace TNL;
using namespace std;

class Game;

class Server
{
public:
    Server();
    virtual ~Server();
    void go();
    bool init();
    void host(const char *host, const char *port);

private:
    GameInterface *mInterface;
    Game *mGame;
    void serviceConnections();

    FRIEND_TEST(network, connectivity);
};

#endif /* SERVER_H_ */

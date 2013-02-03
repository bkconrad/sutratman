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
    
    NetInterface *getInterface();
    void go();
    bool init();
    void host(const char *host, const char *port);

private:
    RefPtr<GameInterface> mInterface;
    Game *mGame;
    void serviceConnections();

    FRIEND_TEST(network, connectivity);
    FRIEND_TEST(network, loopback);
    FRIEND_TEST(player, rpc);
};

#endif /* SERVER_H_ */

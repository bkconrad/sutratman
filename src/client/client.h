#ifndef CLIENT_H_
#define CLIENT_H_

#include "game_connection.h"

#include <gtest/gtest_prod.h>
#include <irrlicht.h>

class GameInterface;
class ClientGame;
class Input;

class Client
{
public:
    Client(GameConnection *connection = NULL, ClientGame *game = NULL);
    virtual ~Client();
    bool connect(char *host);
    void go();
    bool init();
    bool step();
    void serviceConnection();

private:
    GameConnection *mConnection;
    ClientGame *mGame;
    Input *mInput;
    RefPtr<GameInterface> mInterface;

    FRIEND_TEST(network, connectivity);
};

#endif /* CLIENT_H_ */

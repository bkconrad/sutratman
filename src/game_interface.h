#ifndef GAME_INTERFACE_H_
#define GAME_INTERFACE_H_

#include <tnlNetInterface.h>

class Game;
class GameInterface: public TNL::NetInterface
{
public:
    GameInterface(const TNL::Address &address, Game *game);
    virtual ~GameInterface();
    Game *getGame();

private:
    Game *mGame;
};

#endif /* GAME_INTERFACE_H_ */

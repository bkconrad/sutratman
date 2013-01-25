#include "game.h"
#include "game_interface.h"

GameInterface::GameInterface(const TNL::Address &address, Game *game) : NetInterface(address)
{
    mGame = game;
}

GameInterface::~GameInterface()
{
    //dtor
}

Game *GameInterface::getGame()
{
    return mGame;
}


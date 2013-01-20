#include "game_interface.h"
#include "game.h"

GameInterface::GameInterface(const TNL::Address &address, Game* game) : NetInterface(address)
{
   mGame = game;
}

GameInterface::~GameInterface()
{
   //dtor
}

/** @brief getGame
  *
  * @todo: document this function
  */
Game* GameInterface::getGame()
{
   return mGame;
}


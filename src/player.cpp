#include "player.h"

SUT_IMPLEMENT_GAME_ENTITY(Player);

Player::Player(Game* game)
{
   mGame = game;
}

Player::~Player()
{
   //dtor
}

#include "client/client.h"
#include "client/client_game.h"
#include "game.h"
#include "player.h"
#include "server.h"

#include <gtest/gtest.h>
#include <irrlicht.h>

TEST(player, rpc)
{
   int i;
   
   Server s;
   s.init();
   
   ClientGame *clientGame = new ClientGame();
   clientGame->mDriverType = irr::video::EDT_NULL;
   
   Client c;
   // inject a headless game
   c.mGame = clientGame;
   c.init();
   c.loopbackConnect(&s);
   
   for (i = 0; i < 10; i++)
   {
      s.serviceConnections();
      s.mGame->update();
      c.step();
   }

   Player* p = static_cast<ClientGame *>(c.mGame)->mClientEntity;
   irr::core::vector3df start = p->getPos();
   EXPECT_EQ(start, p->getPos());
   
   p->c2sMove(180.0);
   
   for (i = 0; i < 10; i++)
   {
      s.serviceConnections();
      s.mGame->update();
      c.step();
   }
   
   EXPECT_NE(start, p->getPos());
}
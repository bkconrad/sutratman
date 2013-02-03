#include "game.h"
#include "mobile_entity.h"

#include <gtest/gtest.h>

using namespace TNL;

TEST(mobile_entity, packing) {
   MobileEntity *a = new MobileEntity();
   MobileEntity *b = new MobileEntity();
   
   Game g;
   g.initialize();
   g.addEntity(a);
   g.addEntity(b);

   // mock up our source entity
   a->mVelocity = vector3df(.123, .456, .789);

   // we have to make a buffer for the bitstream
   U8 buffer[1024];
   BitStream bitStream(buffer, 1024, 128);

   // pack and unpack the data, measuring bit positions to check for equality
   a->packUpdate(NULL, TNL::U32_MAX, &bitStream);
   U8 packPos = bitStream.getBitPosition();
   bitStream.setBitPosition(0);
   b->unpackUpdate(NULL, &bitStream);
   U8 unPackPos = bitStream.getBitPosition();

   EXPECT_EQ(packPos, unPackPos);
   EXPECT_TRUE(a->isConsistentWith(*b));
}
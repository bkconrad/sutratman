#include "entity.h"

#include <gtest/gtest.h>
#include <tnl.h>

using namespace TNL;

TEST(entity, packing) {
   Entity a;
   Entity b;

   // mock up our source entity
   a.mPos.set(.1234, .4321);
   a.mRot.set(.5678, .8765);

   // we have to make a buffer for the bitstream
   U8 buffer[256];
   BitStream bitStream(buffer, 256, 32);

   // pack and unpack the data, measuring bit positions to check for equality
   a.packUpdate(NULL, TNL::U32_MAX, &bitStream);
   U8 packPos = bitStream.getBitPosition();
   bitStream.setBitPosition(0);
   b.unpackUpdate(NULL, &bitStream);
   U8 unPackPos = bitStream.getBitPosition();

   ASSERT_TRUE(a.isConsistentWith(b));
   ASSERT_EQ(packPos, unPackPos);
}

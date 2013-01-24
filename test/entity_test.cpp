#include "entity.h"

#include <gtest/gtest.h>
#include <tnl.h>

using namespace TNL;

TEST(entity, packing) {
   Entity a;
   Entity b;

   // mock up our source entity
   a.mPos = vec3(.123, .456, .789);
   a.mRot = vec3(.987, .654, .321);

   // we have to make a buffer for the bitstream
   U8 buffer[1024];
   BitStream bitStream(buffer, 1024, 128);

   // pack and unpack the data, measuring bit positions to check for equality
   a.packUpdate(NULL, TNL::U32_MAX, &bitStream);
   U8 packPos = bitStream.getBitPosition();
   bitStream.setBitPosition(0);
   b.unpackUpdate(NULL, &bitStream);
   U8 unPackPos = bitStream.getBitPosition();

   ASSERT_EQ(packPos, unPackPos);
   ASSERT_TRUE(a.isConsistentWith(b));
}

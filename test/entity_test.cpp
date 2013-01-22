#include "entity.h"

#include <gtest/gtest.h>
#include <tnl.h>

using namespace TNL;

TEST(entity, packing) {
   Entity a;
   Entity b;
   a.mPos.set(.1234, .4321);

   // we have to make an array for the bistream
   U8 buffer[256];
   BitStream bitStream(buffer, 256, 32);
   a.packUpdate(NULL, TNL::U32_MAX, &bitStream);
   bitStream.setBitPosition(0);
   b.unpackUpdate(NULL, &bitStream);
   ASSERT_TRUE(a.isConsistentWith(b));
}

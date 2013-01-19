#include "client/video.h"
#include "gtest/gtest.h"
TEST(video, sanity_test) {
   Video v;
   ASSERT_TRUE(v.run());
}

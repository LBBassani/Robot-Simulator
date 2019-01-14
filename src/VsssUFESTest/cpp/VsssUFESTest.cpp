#include <gtest/gtest.h>
#include "VsssUFES.h"

TEST(VsssUFESTest, CheckCapitalisation) {
    VsssUFES g("GradleUser");
    EXPECT_EQ(g.getNameLength(), 10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
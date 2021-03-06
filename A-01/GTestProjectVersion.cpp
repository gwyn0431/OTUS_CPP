#include "gtest/gtest.h"
#include "ProjectVersionManager.h"

FProjectVersion ProjectVersion = UProjectVersionManager::GetProjectVersion();

TEST(TestProjectVersion, IsProjectVersionCorrect) {
  EXPECT_GE(ProjectVersion.Major, 0);
  EXPECT_GE(ProjectVersion.Minor, 0);
  EXPECT_GT(ProjectVersion.Patch, 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
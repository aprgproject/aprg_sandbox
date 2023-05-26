#include <AprgUniqueProblems/GreedyAlgorithm/SweepLine/MinimumNumberOfPlatformsRequiredForARailwayStation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MinimumNumberOfPlatformsRequiredForARailwayStationTest, GetMinimumNumberOfPlatformsWorksForExample1) {
    MinimumNumberOfPlatformsRequiredForARailwayStation maximumEmployeeCount;

    maximumEmployeeCount.addTrainSchedule(900, 910);
    maximumEmployeeCount.addTrainSchedule(940, 1200);
    maximumEmployeeCount.addTrainSchedule(950, 1120);
    maximumEmployeeCount.addTrainSchedule(1100, 1130);
    maximumEmployeeCount.addTrainSchedule(1500, 1900);
    maximumEmployeeCount.addTrainSchedule(1800, 2000);

    EXPECT_EQ(3, maximumEmployeeCount.getMinimumNumberOfPlatforms());
}

TEST(MinimumNumberOfPlatformsRequiredForARailwayStationTest, GetMinimumNumberOfPlatformsWorksForExample2) {
    MinimumNumberOfPlatformsRequiredForARailwayStation maximumEmployeeCount;

    maximumEmployeeCount.addTrainSchedule(900, 910);
    maximumEmployeeCount.addTrainSchedule(940, 1200);

    EXPECT_EQ(1, maximumEmployeeCount.getMinimumNumberOfPlatforms());
}

}  // namespace alba
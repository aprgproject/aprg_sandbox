#include <AprgUniqueProblems/GreedyAlgorithm/SweepLine/MinimumNumberOfPlatformsRequiredForARailwayStation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MinimumNumberOfPlatformsRequiredForARailwayStationTest, GetMinimumNumberOfPlatformsWorksForExample1)
{
    MinimumNumberOfPlatformsRequiredForARailwayStation maximumEmployeeCount;

    maximumEmployeeCount.addTrainSchedule(900U, 910U);
    maximumEmployeeCount.addTrainSchedule(940U, 1200U);
    maximumEmployeeCount.addTrainSchedule(950U, 1120U);
    maximumEmployeeCount.addTrainSchedule(1100U, 1130U);
    maximumEmployeeCount.addTrainSchedule(1500U, 1900U);
    maximumEmployeeCount.addTrainSchedule(1800U, 2000U);

    EXPECT_EQ(3U, maximumEmployeeCount.getMinimumNumberOfPlatforms());
}

TEST(MinimumNumberOfPlatformsRequiredForARailwayStationTest, GetMinimumNumberOfPlatformsWorksForExample2)
{
    MinimumNumberOfPlatformsRequiredForARailwayStation maximumEmployeeCount;

    maximumEmployeeCount.addTrainSchedule(900U, 910U);
    maximumEmployeeCount.addTrainSchedule(940U, 1200U);

    EXPECT_EQ(1U, maximumEmployeeCount.getMinimumNumberOfPlatforms());
}

}

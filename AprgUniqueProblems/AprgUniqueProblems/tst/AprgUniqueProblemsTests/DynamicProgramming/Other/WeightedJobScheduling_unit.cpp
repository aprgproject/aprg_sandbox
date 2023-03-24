#include <AprgUniqueProblems/DynamicProgramming/Other/WeightedJobScheduling.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(WeightedJobSchedulingTest, GetMaxProfitWorksOnEmpty)
{
    WeightedJobScheduling queryForTest({});

    EXPECT_EQ(0U, queryForTest.getMaxProfitByMonitoringTimeStampsUsingIterativeDP());
    EXPECT_EQ(0U, queryForTest.getMaxProfitByMonitoringJobsUsingIterativeDP());
}

TEST(WeightedJobSchedulingTest, GetMaxProfitWorksOnExample1)
{
    WeightedJobScheduling queryForTest({{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}});

    EXPECT_EQ(250U, queryForTest.getMaxProfitByMonitoringTimeStampsUsingIterativeDP());
    EXPECT_EQ(250U, queryForTest.getMaxProfitByMonitoringJobsUsingIterativeDP());
}

}

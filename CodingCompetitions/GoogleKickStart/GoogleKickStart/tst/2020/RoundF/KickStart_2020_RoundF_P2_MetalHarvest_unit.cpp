#include "KickStart_2020_RoundF_P2_MetalHarvest.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundF_P2_MetalHarvest {

TEST(KickStart_2020_RoundF_P2_MetalHarvestTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "2    "
                         "\n"
                      << "3 5  "
                         "\n"
                      << "1 5  "
                         "\n"
                      << "10 11"
                         "\n"
                      << "8 9  "
                         "\n"
                      << "3 2  "
                         "\n"
                      << "1 2  "
                         "\n"
                      << "3 5  "
                         "\n"
                      << "13 14"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 2"
        "\n"
        "Case #2: 3"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2020_RoundF_P2_MetalHarvest

/*
Problem

You are in charge of deploying robots to harvest Kickium from a nearby asteroid. Robots are not designed to work as a
team, so only one robot can harvest at any point of time. A single robot can be deployed for up to K units of time in a
row before it returns for calibration, regardless of how much time it spends on harvesting during that period.
Harvesting can only be done during specific time intervals. These time intervals do not overlap. Given K and the time
intervals in which harvesting is allowed, what is the minimum number of robot deployments required to harvest at all
possible times? Input

The first line of the input gives the number of test cases, T. T test cases follow.

The first line of each test case gives two space separated integers N and K: the number of time intervals in which
harvesting is allowed, and the maximum duration a robot can be deployed for before returning for calibration.

The next N lines contain a pair of space separated integers Si and Ei: the start time and the end time of the i-th
interval respectively. Please note that intervals don't include the time unit starting at the moment Ei, so for example
an interval with (Si = 2; Ei = 5) has duration of 3 time units.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is
the number of times robot deployment is needed so that for each interval there is one robot harvesting at that time.
Limits

1 ≤ T ≤ 100.
Time limit: 20 seconds per test set.
Memory limit: 1GB.
All Si are distinct.
For any two intervals (Si,Ei) and (Sj,Ej) with Si < Sj, Ei < Sj.
Test Set 1

1 ≤ N ≤ 100.
1 ≤ K ≤ 100.
1 ≤ Si < Ei ≤ 200.
Test Set 2

100 < N ≤ 105, in at most 10 test cases.
1 ≤ N ≤ 100, in the remaining test cases.
1 ≤ K ≤ 109.
1 ≤ Si < Ei ≤ 109.
Sample

Input

Output


2
3 5
1 5
10 11
8 9
3 2
1 2
3 5
13 14





Case #1: 2
Case #2: 3


In Sample Case #1, we deploy the robot at time instant 1 and it becomes available for the interval [1, 6]. However, it
harvests only for the time range [1, 5]. After that we deploy the robot at 6 and it becomes available for the time
interval [6, 11]. This deployment covers both the remaining intervals [8, 9] and [10, 11]. There are multiple optimal
strategies here. For example, we can deploy the second robot at 7. It would then cover the range [7, 12], thus
harvesting for the intervals [8, 9] and [10, 11].

In Sample Case #2, we deploy the robot at time instant 1, and it becomes available for [1, 3], but harvests for [1, 2]
as [2, 3] is not part of any interval. After that we deploy the robot at 3 for the time range [3, 5] in which the robot
harvests for the interval [3, 5]. The third deployment is done at time instant 13 making the robot available for time
range [13, 15]. However, it harvests only for the interval [13, 14]. Thus three deployments are needed to cover all the
intervals.

*/

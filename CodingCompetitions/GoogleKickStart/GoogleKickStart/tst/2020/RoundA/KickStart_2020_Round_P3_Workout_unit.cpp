#include "KickStart_2020_Round_P3_Workout.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_Round_P3_Workout {

TEST(KickStart_2020_Round_P3_WorkoutTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "1          "
                         "\n"
                      << "3 1        "
                         "\n"
                      << "100 200 230"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 50"
        "\n",
        outputStringStream.str());
}

TEST(KickStart_2020_Round_P3_WorkoutTest, Test2) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "3               "
                         "\n"
                      << "5 2             "
                         "\n"
                      << "10 13 15 16 17  "
                         "\n"
                      << "5 6             "
                         "\n"
                      << "9 10 20 26 30   "
                         "\n"
                      << "8 3             "
                         "\n"
                      << "1 2 3 4 5 6 7 10"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 2"
        "\n"
        "Case #2: 3"
        "\n"
        "Case #3: 1"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2020_Round_P3_Workout

/*
Problem

Tambourine has prepared a fitness program so that she can become more fit! The program is made of N sessions. During the
i-th session, Tambourine will exercise for Mi minutes. The number of minutes she exercises in each session are strictly
increasing.

The difficulty of her fitness program is equal to the maximum difference in the number of minutes between any two
consecutive training sessions.

To make her program less difficult, Tambourine has decided to add up to K additional training sessions to her fitness
program. She can add these sessions anywhere in her fitness program, and exercise any positive integer number of minutes
in each of them. After the additional training session are added, the number of minutes she exercises in each session
must still be strictly increasing. What is the minimum difficulty possible? Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line
containing the two integers N and K. The second line contains N integers, the i-th of these is Mi, the number of minutes
she will exercise in the i-th session. Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is
the minimum difficulty possible after up to K additional training sessions are added. Limits

Time limit: 20 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
For at most 10 test cases, 2 ≤ N ≤ 105.
For all other test cases, 2 ≤ N ≤ 300.
1 ≤ Mi ≤ 109.
Mi < Mi+1 for all i.
Test set 1

K = 1.
Test set 2

1 ≤ K ≤ 105.
Samples

Input 1

Output 1


1
3 1
100 200 230




Case #1: 50



Input 2

Output 2


3
5 2
10 13 15 16 17
5 6
9 10 20 26 30
8 3
1 2 3 4 5 6 7 10




Case #1: 2
Case #2: 3
Case #3: 1


Sample #1

In Case #1: Tambourine can add up to one session. The added sessions are marked in bold: 100 150 200 230. The difficulty
is now 50.

Sample #2

In Case #1: Tambourine can add up to two sessions. The added sessions are marked in bold: 10 11 13 15 16 17 18. The
difficulty is now 2.

In Case #2: Tambourine can add up to six sessions. The added sessions are marked in bold: 9 10 12 14 16 18 20 23 26
29 30. The difficulty is now 3.

In Case #3: Tambourine can add up to three sessions. The added sessions are marked in bold: 1 2 3 4 5 6 7 8 9 10. The
difficulty is now 1. Note that Tambourine only added two sessions.

    Note #1: Only Sample #1 is a valid input for Test set 1. Consequently, Sample #1 will be used as a sample test set
for your submissions. Note #2: Unlike previous editions, in Kick Start 2020, all test sets are visible verdict test
sets, meaning you receive instant feedback upon submission.
*/

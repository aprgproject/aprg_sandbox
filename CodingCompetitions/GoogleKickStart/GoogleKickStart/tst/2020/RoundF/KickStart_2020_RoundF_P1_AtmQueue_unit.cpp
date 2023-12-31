#include "KickStart_2020_RoundF_P1_AtmQueue.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundF_P1_AtmQueue {

TEST(KickStart_2020_RoundF_P1_AtmQueueTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << "2         "
                         "\n"
                      << "3 3       "
                         "\n"
                      << "2 7 4     "
                         "\n"
                      << "5 6       "
                         "\n"
                      << "9 10 4 7 2"
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        "Case #1: 1 3 2"
        "\n"
        "Case #2: 3 5 1 2 4"
        "\n",
        outputStringStream.str());
}

}  // namespace KickStart_2020_RoundF_P1_AtmQueue

/*
Problem

There are N people numbered from 1 to N, standing in a queue to withdraw money from an ATM. The queue is formed in
ascending order of their number. The person numbered i wants to withdraw amount Ai. The maximum amount a person can
withdraw at a time is X. If they need more money than X, they need to go stand at the end of the queue and wait for
their turn in line. A person leaves the queue once they have withdrawn the required amount.

You need to find the order in which all the people leave the queue.
Input

The first line of the input gives the number of test cases T. T test cases follow.

The first line of each test case gives two space separated integers: the number of people standing in the queue, N and
the maximum amount X that can be withdrawn in one turn.

The next line contains N space separated integers Ai.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is
the space separated list of integers that denote the order in which the people leave the queue. Limits

Time limit: 20 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
Test Set 1

1 ≤ N ≤ 100.
1 ≤ Ai ≤ 100.
1 ≤ X ≤ 100.
Test Set 2

1 ≤ N ≤ 105 for at most 10 test cases. For the remaining cases, 1 ≤ N ≤ 100
1 ≤ Ai ≤ 109.
1 ≤ X ≤ 109.
Sample

Input

Output


2
3 3
2 7 4
5 6
9 10 4 7 2





Case #1: 1 3 2
Case #2: 3 5 1 2 4


In Sample Case #1, there are 3 people and the limit to withdraw in one turn is 3. Below is step-by-step description of
how the process will look like:

    The queue initially looks like [1, 2, 3]. The first person withdraws an amount of 2 in their first attempt and
leaves the queue. The queue now looks like [2, 3]. The second person wants to withdraw an amount of 7, but they can
withdraw only 3 in their first turn. Since they still need to withdraw an amount of 4, they have to rejoin the queue at
the end of the line. The queue now looks like [3, 2]. The third person needs to withdraw an amount of 4 but they can
only withdraw 3 in their first turn so, they rejoin the queue at the end of the line to withdraw amount of 1 later. The
queue now looks like [2, 3]. The second person still needs to withdraw an amount of 4. They withdraw an amount of 3 in
their second turn and waits for their next turn to arrive to withdraw the remaining amount of 1. The queue now looks
like [3, 2]. The third person withdraws the remaining amount of 1 and leaves the queue. The queue now looks like [2].
The second person withdraws the remaining amount of 1 and leaves the queue. The queue is now empty.

The order in which people leave the queue is [1, 3, 2].

In Sample Case #2, there are 5 people and the limit to withdraw in one turn is 6. Below is step-by-step description of
how the process will look like:

    The queue initially looks like [1, 2, 3, 4, 5]. The first person withdraws an amount of 6, and joins at the end
again to withdraw the remaining amount of 3 later. The queue looks like [2, 3, 4, 5, 1]. The second person similarly
withdraws an amount of 6 and waits for his next turn to withdraw an amount of 4. The queue looks like [3, 4, 5, 1, 2].
The third person withdraws an amount of 4 and leaves the queue. The queue now looks like [4, 5, 1, 2]. The fourth person
withdraws 6 and waits for his next turn. The queue looks like [5, 1, 2, 4]. The fifth person withdraws amount of 2 and
leaves the queue. The queue looks like, [1, 2, 4]. All other people now leave the queue after their second turn one by
one.

The order in which people leave the queue is [3, 5, 1, 2, 4].
*/

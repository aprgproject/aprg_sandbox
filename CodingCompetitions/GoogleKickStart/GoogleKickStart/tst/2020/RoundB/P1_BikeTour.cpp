// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "P1_BikeTour.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace P1_BikeTour
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber)
{
    int N; my_cin >> N;
    vector<int> H(N);
    for (int& a : H) my_cin >> a;
    int ans = 0;
    for (int i = 1; i+1 < N; i++) {
        ans += (H[i] > H[i-1]) && H[i] > H[i+1];
    }

    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
}

void runAllTestCases()
{
    unsigned int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (unsigned int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++)
    {
        runTestCase(testCaseNumber);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

/*
Problem

Li has planned a bike tour through the mountains of Switzerland. His tour consists of N checkpoints, numbered from 1 to N in the order he will visit them. The i-th checkpoint has a height of Hi.

A checkpoint is a peak if:

    It is not the 1st checkpoint or the N-th checkpoint, and
    The height of the checkpoint is strictly greater than the checkpoint immediately before it and the checkpoint immediately after it.

Please help Li find out the number of peaks.
Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the integer N. The second line contains N integers. The i-th integer is Hi.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the number of peaks in Li's bike tour.
Limits

Time limit: 10 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
1 ≤ Hi ≤ 100.
Test set 1

3 ≤ N ≤ 5.
Test set 2

3 ≤ N ≤ 100.
Sample

Input

Output


4
3
10 20 14
4
7 7 7 7
5
10 90 20 90 10
3
10 3 10





Case #1: 1
Case #2: 0
Case #3: 2
Case #4: 0



    In sample case #1, the 2nd checkpoint is a peak.
    In sample case #2, there are no peaks.
    In sample case #3, the 2nd and 4th checkpoint are peaks.
    In sample case #4, there are no peaks.
*/

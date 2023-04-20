// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundD_P2_AlienPiano.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <array>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundD_P2_AlienPiano
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

int signum(int a) { return (a > 0) - (a < 0); }
int compare(int a, int b) { return signum(a - b); }

void runTestCase(unsigned int const testCaseNumber)
{
    int N;
    my_cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        my_cin >> A[i];
    array<int, 4> dp{0,0,0,0};
    for (int i = 1; i < N; i++) {
        array<int, 4> ndp{N+1, N+1, N+1, N+1};
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                ndp[y] = min(ndp[y], dp[x] + (compare(x, y) != compare(A[i-1], A[i])));
            }
        }
        dp = ndp;
    }

    int ans = std::min({dp[0], dp[1], dp[2], dp[3]});

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



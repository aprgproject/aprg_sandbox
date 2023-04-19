// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "P3_Toys.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace P3_Toys
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber)
{
    int N;
    my_cin >> N;
    vector<int64_t> E(N);
    vector<pair<int64_t, int>> R(N);
    for (int i = 0; i < N; i++) {
        my_cin >> E[i] >> R[i].first;
        R[i].first += E[i];
        R[i].second = i;
    }
    sort(R.begin(), R.end());

    int64_t C = std::accumulate(E.begin(), E.end(), int64_t(0));

    // compute prefix sums of alive toys
    vector<int64_t> bit(N);
    for (int i = 0; i < N; i++) {
        for (int a = i; a < N; a |= a+1) {
            bit[a] += E[i];
        }
    }

    priority_queue<int, vector<int>, greater<int>> is_bad;

    const int64_t INF = 8e18;
    int64_t ans = -1;
    int best_remove = -1;
    for (int z = 0; z < N; z++) {
        while (!R.empty() && C < R.back().first) {
            is_bad.push(R.back().second);
            R.pop_back();
        }

        if (is_bad.empty()) {
            ans = INF;
            best_remove = z;
            break;
        }

        int cur = is_bad.top(); is_bad.pop();
        int64_t cnd = C;
        for (int a = cur; a > 0; a &= a-1) {
            cnd += bit[a-1];
        }
        if (cnd > ans) {
            ans = cnd;
            best_remove = z;
        }

        C -= E[cur];
        for (int a = cur; a < N; a |= a+1) {
            bit[a] -= E[cur];
        }
    }

    my_cout << "Case #" << testCaseNumber << ": ";
    my_cout << best_remove << ' ';
    if (ans == INF) my_cout << "INDEFINITELY" << '\n';
    else my_cout << ans << '\n';
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



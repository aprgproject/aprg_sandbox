// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundG_P3_CombinationLock.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundG_P3_CombinationLock
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber)
{
    int n, k;
    my_cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        my_cin >> a[i];
        a[i]--;
    }
    sort(a.begin(), a.end());
    long long best_answer = numeric_limits<long long>::max();
    int L = 0, R = 0;
    long long current = 0;
    for(int i = 1; i < n; ++i) {
        current += k - a[i];
    }
    int cnt_minus = 0;
    for(int me = 0; me < n; ++me) {
        if(me != 0) {
            current -= a[me];
            cnt_minus--;
        }
        while(R + 1 < n && a[R+1] - a[me] <= k / 2) {
            ++R;
            current -= k - a[R];
            current += a[R];
            cnt_minus++;
        }
        while(a[me] - a[L] > k / 2) {
            current -= -a[L];
            current += k + a[L];
            cnt_minus++;
            ++L;
        }
        long long maybe = current + (long long) (n - 1 - 2 * cnt_minus) * a[me];
        best_answer = min(best_answer, maybe);
        current += -a[me];
    }
    my_cout << "Case #" << testCaseNumber << ": " << best_answer << '\n';
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



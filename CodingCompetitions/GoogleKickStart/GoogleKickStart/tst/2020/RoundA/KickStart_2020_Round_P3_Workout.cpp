// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_Round_P3_Workout.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_Round_P3_Workout {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

int n, k, a[100000];

void runTestCase(int const testCaseNumber) {
    my_cin >> n >> k;
    for (int i = 0; i < n; ++i) my_cin >> a[i];
    int lb = 1, rb = a[n - 1] - a[0];
    while (lb < rb) {
        int mb = (lb + rb) / 2;        int k2 = 0;
        for (int i = 1; i < n; ++i) {
            int d = a[i] - a[i - 1];
            // ceil(d/(n+1))<=mb
            // d<=mb*(n+1)
            // d/mb-1<=n
            k2 += (d + mb - 1) / mb - 1;
        }
        if (k2 <= k)
            rb = mb;
        else
            lb = mb + 1;
    }
    my_cout << "Case #" << testCaseNumber << ": " << lb << '\n';
}

void runAllTestCases() {
    int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
        runTestCase(testCaseNumber);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);
    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}  // namespace KickStart_2020_Round_P3_Workout
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#include "KickStart_2020_RoundH_P3_Rugby.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
using namespace alba;
namespace KickStart_2020_RoundH_P3_Rugby {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber) {
    int N;
    my_cin >> N;
    vector<int64_t> X(N);
    vector<int64_t> Y(N);
    for (int i = 0; i < N; i++) {
        my_cin >> X[i] >> Y[i];
    }
    sort(X.begin(), X.end());
    for (int i = 0; i < N; i++) X[i] -= i;
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    int64_t mx = X[N / 2];
    int64_t my = Y[N / 2];
    int64_t ans = 0;
    for (auto& x : X) ans += abs(x - mx);
    for (auto& y : Y) ans += abs(y - my);

    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
}

void runAllTestCases() {
    unsigned int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (unsigned int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
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
}  // namespace KickStart_2020_RoundH_P3_Rugby
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

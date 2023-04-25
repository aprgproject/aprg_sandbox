// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundE_P2_HighBuildings.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundE_P2_HighBuildings {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber) {
    int N, A, B, C;
    my_cin >> N >> A >> B >> C;

    assert(1 <= C && C <= N);
    assert(C <= A && A <= N);
    assert(C <= B && B <= N);

    my_cout << "Case #" << testCaseNumber << ": ";
    if ((A + B - C) > N || (A + B - C == 1 && N >= 2)) {
        my_cout << "IMPOSSIBLE" << '\n';
    } else if (N == 1) {
        my_cout << "1" << '\n';
    } else if (N == 2) {
        if (C == 2) {
            my_cout << "1 1" << '\n';
        } else if (A == 2) {
            my_cout << "1 2" << '\n';
        } else if (B == 2) {
            my_cout << "2 1" << '\n';
        } else
            assert(false);
    } else {
        vector<int> res;
        res.reserve(N);
        for (int i = 0; i < A - C; i++) res.push_back(2);
        for (int i = 0; i < C; i++) res.push_back(3);
        for (int i = 0; i < B - C; i++) res.push_back(2);
        int extra = N - (A + B - C);
        if (extra > 0) {
            res.insert(res.begin() + 1, extra, 1);
        }
        for (int i = 0; i < N; i++) {
            my_cout << res[i] << " \n"[i + 1 == N];
        }
    }
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
}  // namespace KickStart_2020_RoundE_P2_HighBuildings
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

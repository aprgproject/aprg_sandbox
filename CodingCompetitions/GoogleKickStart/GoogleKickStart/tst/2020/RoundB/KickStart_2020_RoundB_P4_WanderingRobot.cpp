// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundB_P4_WanderingRobot.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundB_P4_WanderingRobot
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

vector<long double> logFact(int(3.1e5));

void runTestCase(unsigned int const testCaseNumber)
{
    int X, Y; my_cin >> X >> Y;
    int Xlo, Xhi, Ylo, Yhi;
    my_cin >> Xlo >> Ylo >> Xhi >> Yhi;

    auto probPath = [&](int r, int c) -> long double {
        return exp(logFact[r+c] - logFact[r] - logFact[c] - (r+c) * log(2.L));
    };
    // we'll just casework on the first entry
    vector<long double> sumAnds;
    if (Ylo > 1) {
        for (int x = Xlo; x <= Xhi; x++) {
            sumAnds.push_back(0.5 * probPath(x - 1, Ylo - 2));
        }
        if (Xhi == X) {
            for (int y = 1; y < Ylo; y++) {
                sumAnds.push_back(0.5 * probPath(X - 1, y - 1));
            }
        }
    }
    if (Xlo > 1) {
        for (int y = Ylo; y <= Yhi; y++) {
            sumAnds.push_back(0.5 * probPath(Xlo - 2, y - 1));
        }
        if (Yhi == Y) {
            for (int x = 1; x < Xlo; x++) {
                sumAnds.push_back(0.5 * probPath(x - 1, Y - 1));
            }
        }
    }
    sort(sumAnds.begin(), sumAnds.end());
    long double ans = 0;
    for (auto a : sumAnds) ans += a;
    ans = 1 - ans;

    my_cout.precision(10);
    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
}

void runAllTestCases()
{
    for (int i = 1; i < int(logFact.size()); i++) {
        logFact[i] = logFact[i-1] + log((long double)(i));
    }

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



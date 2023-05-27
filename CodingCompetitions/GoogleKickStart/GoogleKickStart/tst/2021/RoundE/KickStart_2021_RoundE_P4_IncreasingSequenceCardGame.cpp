// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2021_RoundE_P4_IncreasingSequenceCardGame.hpp"

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
namespace KickStart_2021_RoundE_P4_IncreasingSequenceCardGame {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(int const testCaseNumber) {
    // my_cout << "Case #" << testCaseNumber << ": " << answer << '\n';
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
}  // namespace KickStart_2021_RoundE_P4_IncreasingSequenceCardGame
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

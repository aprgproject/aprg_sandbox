// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
// NOTE: Remember to delete "fake_"
#include "P1_Retype.hpp"
#include <Common/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
using namespace alba;
namespace P1_Retype
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

void runTestCase(unsigned int const testCaseNumber)
{
    int64_t n, k, s;
    fake_cin >> n >> k >> s;
    int64_t answer = min(n+1, (k-s)+(n-s)+1) + (k-1);

    fake_cout << "Case #" << testCaseNumber << ": " << answer << '\n';
}

void runAllTestCases()
{
    unsigned int numberOfTestCases;
    fake_cin >> numberOfTestCases;
    for (unsigned int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++)
    {
        runTestCase(testCaseNumber);
    }
}

int fake_main()
{
    ios_base::sync_with_stdio(false);
    fake_cin.tie(nullptr);

    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "CodeJam_2019_WorldFinals_P2_SortingPermutationUnit.hpp"
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
namespace CodeJam_2019_WorldFinals_P2_SortingPermutationUnit
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber)
{
    //my_cout << "Case #" << testCaseNumber << ": " << answer << '\n';
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




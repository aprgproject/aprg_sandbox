// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_PracticeRound_P2_Mural.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_PracticeRound_P2_Mural
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
    string s;
    my_cin >> s;
    vector<int> b(N+1);
    for(int i = 0; i < N; ++i) b[i+1] = b[i] + s[i] - '0';
    int l = (N+1)/2, ret = 0;
    for(int i = 0; i+l-1 < N; ++i){
      ret = max(ret,b[i+l]-b[i]);
    }
    my_cout << "Case #" << testCaseNumber << ": " << ret << '\n';
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



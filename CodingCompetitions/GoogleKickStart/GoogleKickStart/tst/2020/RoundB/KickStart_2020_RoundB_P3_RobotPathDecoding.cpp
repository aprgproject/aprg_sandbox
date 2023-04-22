// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundB_P3_RobotPathDecoding.hpp"
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
namespace KickStart_2020_RoundB_P3_RobotPathDecoding
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

typedef long long ll;

void runTestCase(unsigned int const testCaseNumber)
{
    string s;
    my_cin >> s;
    ll mod = 1e9;
    ll x = 0, y = 0;
    vector<ll> mul = {1};
    for (char c : s) {
      if (c >= '2' && c <= '9')
    mul.push_back(mul.back()*(c-'0')%mod);
      else if (c == 'E') x = (x+mul.back())%mod;
      else if (c == 'W') x = ((x-mul.back())%mod+mod)%mod;
      else if (c == 'S') y = (y+mul.back())%mod;
      else if (c == 'N') y = ((y-mul.back())%mod+mod)%mod;
      else if (c == '(') continue;
      else if (c == ')') mul.pop_back();
      else assert(0);
    }
    my_cout << "Case #" << testCaseNumber << ": "  << x+1 << ' ' << y+1 << '\n';
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



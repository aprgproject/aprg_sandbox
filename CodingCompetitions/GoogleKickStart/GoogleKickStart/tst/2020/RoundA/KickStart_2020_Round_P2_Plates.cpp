// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_Round_P2_Plates.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <cstring>
#include <iostream>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_Round_P2_Plates
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

int n, k, p, a[50][30];
int dp[51][1501];

void runTestCase(unsigned int const testCaseNumber)
{
    my_cin >> n >> k >> p;
    memset(dp, 0xc0, sizeof(dp));
    dp[0][0]=0;
    for(int i=0; i<n; ++i) {
        memcpy(dp[i+1], dp[i], sizeof(dp[0]));
        for(int j=0, s=0; j<k; ++j) {
            my_cin >> a[i][j];
            s+=a[i][j];
            //use j+1 plates
            for(int l=0; l+j+1<=p; ++l)
                dp[i+1][l+j+1]=max(dp[i][l]+s, dp[i+1][l+j+1]);
        }
    }
    my_cout << "Case #" << testCaseNumber << ": " << dp[n][p] << '\n';
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



// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundC_P3_PerfectSubarray.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <cstring>
#include <iostream>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundC_P3_PerfectSubarray
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

#define ll long long
const int mxN=1e5;
int n, a[mxN], c[2*100*mxN+1];

void runTestCase(unsigned int const testCaseNumber)
{
    my_cin >> n;
    int s1=0, s2=0;
    for(int i=0; i<n; ++i) {
        my_cin >> a[i];
        if(a[i]<0)
            s1-=a[i];
        else
            s2+=a[i];
    }
    int t=0;
    ll ans=0;
    ++c[s1];
    for(int i=0; i<n; ++i) {
        t+=a[i];
        for(int j=0; j*j<=s2; ++j) {
            if(s1+(t-j*j)>=0)
            ans+=c[s1+(t-j*j)];
        }
        ++c[s1+t];
    }
    memset(c, 0, 4*(s1+s2+1));

    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
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



// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#include "P2_BoringNumbers.hpp"
#include <Common/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
using namespace alba;
namespace P2_BoringNumbers
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber)
{
    int64_t L, R;
    my_cin >> L >> R;
    ++R;
    bool parity = 0;
    int64_t coeff = 1;    int64_t ans = 0;
    while (L < R)
    {
        auto is_good = [&](int64_t v)
        {
            bool d = v % 2;
            while (v > 0) {
                if (v % 2 != d) return false;
                d = !d;
                v /= 10;
            }
            return d == 0;
        };
        while (L < R && L % 10 != 0)
        {
            if (is_good(L)) {
                ans += coeff;
            }
            L++;
        }
        while (L < R && R % 10 != 0)
        {
            --R;
            if (is_good(R)) {
                ans += coeff;
            }
        }

        if (L == R) break;

        L /= 10;
        R /= 10;

        coeff *= 5;
        parity = !parity;
    }
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
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~



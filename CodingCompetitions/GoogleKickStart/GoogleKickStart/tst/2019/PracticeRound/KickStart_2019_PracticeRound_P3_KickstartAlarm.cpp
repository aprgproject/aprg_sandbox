// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_PracticeRound_P3_KickstartAlarm.hpp"

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
namespace KickStart_2019_PracticeRound_P3_KickstartAlarm {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

const long long MAX_MODULO = 1000000007;
long long N, K, x1, y1, C, D, E1, E2, F;

long long raiseToPower(long long a, long long p) {
    long long result = 1, cp = a;
    while (p) {
        if (p & 1) result = (result * cp) % MAX_MODULO;  // is even
        p >>= 1;                                         // divide by two
        cp = (cp * cp) % MAX_MODULO;
    }
    return result;
}

void buildA(vector<long long>& A) {
    A[0] = (x1 + y1) % F;
    long long CD = C + D, E = E1 + E2;
    for (long long i = 1; i < static_cast<decltype(i)>(A.size()); ++i) {
        A[i] = (CD * A[i - 1] + E) % F;
    }
}

long long getGeometricTerm(long long i, long long k) {
    // There is some math here that I cannot understand.
    if (i == 1) {
        return k % MAX_MODULO;
    } else {
        // Geometric term is (p^(K+1)-1)/(p-1)
        // Using inverse modulo:
        // inverseModulo ≅ 1/(p-1)
        // (1/(p-1) * inverseModulo) mod m = 1
        // Using fermats little theorem:
        // -> Fermat's little theorem states that if p is a prime number, then for any integer a, the number a^p − a is
        // an integer multiple of p.
        // -> a^(m-1) ≅ 1 (mod m)
        // -> a^(-1) ≅ a^(m-2) (mod m)
        // Thus 1/(p-1) = (p-1)^(-1) = (p-1)^(m-2)
        return ((i * (raiseToPower(i, k) - 1) % MAX_MODULO) * raiseToPower(i - 1, MAX_MODULO - 2)) % MAX_MODULO;
    }
}

void runTestCase(int const testCaseNumber) {
    my_cin >> N >> K >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
    vector<long long> A(N);
    buildA(A);

    // The summation of a geometric progression, it can also be written as Ax * (p^(K+1)-1)/(p-1).    long long geometricSum = 0, numberOfInstances = 1, currentK = N, totalPower = 0;
    for (long long i = N - 1; i >= 0; --i) {
        geometricSum = (geometricSum + numberOfInstances * A[i]) % MAX_MODULO;
        ++numberOfInstances;
        totalPower = (totalPower + geometricSum * getGeometricTerm(currentK, K)) % MAX_MODULO;
        --currentK;
    }
    my_cout << "Case #" << testCaseNumber << ": " << totalPower << '\n';
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
}  // namespace KickStart_2019_PracticeRound_P3_KickstartAlarm
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#include "P4_Friends.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
using namespace alba;
namespace P4_Friends
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber)
{
    int N, Q;
    my_cin >> N >> Q;
    const int INF = 1e9;
    vector<vector<int>> dist(26, vector<int>(26, INF));
    for (int i = 0; i < 26; i++) dist[i][i] = 0;

    vector<int> msks(N);
    for (int z = 0; z < N; z++) {
        string S;
        my_cin >> S;
        int msk = 0;
        for (char c : S) {
            msk |= (1 << (c - 'A'));
        }
        msks[z] = msk;
        for (int i = 0; i < 26; i++) {
            if (!(msk & (1 << i))) continue;            for (int j = i+1; j < 26; j++) {
                if (!(msk & (1 << j))) continue;
                dist[i][j] = dist[j][i] = 1;
            }
        }
    }

    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    my_cout << "Case #" << testCaseNumber << ":";
    for (int q = 0; q < Q; q++) {
        int u, v; my_cin >> u >> v; u--, v--;
        int ans = INF;
        for (int m1 = msks[u]; m1; m1 &= m1-1) {
            int i = __builtin_ctz(m1);
            for (int m2 = msks[v]; m2; m2 &= m2-1) {
                int j = __builtin_ctz(m2);
                ans = min(ans, 2 + dist[i][j]);
            }        }
        if (ans == INF) ans = -1;
        my_cout << ' ' << ans;
    }
    my_cout << '\n';
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



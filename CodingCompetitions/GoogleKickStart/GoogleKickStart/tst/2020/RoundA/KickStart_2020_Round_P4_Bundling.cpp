// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_Round_P4_Bundling.hpp"

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
namespace KickStart_2020_Round_P4_Bundling {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

int n, k, c[2000001][26], m, cnt[2000001];
long long ans;

void dfs(int u = 0, int d = 0) {
    for (int v = 0; v < 26; ++v)
        if (c[u][v]) dfs(c[u][v], d + 1), cnt[u] += cnt[c[u][v]];
    while (cnt[u] >= k) {
        cnt[u] -= k;
        ans += d;
    }
}

void runTestCase(int const testCaseNumber) {
    my_cin >> n >> k;
    m = 1;
    for (int i = 0; i < n; ++i) {
        string s;
        my_cin >> s;
        int u = 0;
        for (char d : s) {
            if (!c[u][d - 'A']) c[u][d - 'A'] = m++;
            u = c[u][d - 'A'];
        }
        ++cnt[u];
    }
    ans = 0;
    dfs();
    memset(c, 0, m * sizeof(c[0]));
    memset(cnt, 0, m * 4);
    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';
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
}  // namespace KickStart_2020_Round_P4_Bundling
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

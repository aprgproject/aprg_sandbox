// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundF_P3_PaintersDuel.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundF_P3_PaintersDuel {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using ll = long long;

vector<int> g[36];
map<ll, int> ok[10][36][36][2];
int id[20][20];

bool can_move(ll ban, int a) {
    for (int x : g[a]) {
        if ((ban >> x) & 1) continue;
        return true;
    }
    return false;
}

void dfs(int v, ll &mask, ll ban) {
    if ((mask >> v) & 1) return;
    mask |= (1ll << v);
    for (int x : g[v]) {
        if ((ban >> x) & 1) continue;
        dfs(x, mask, ban);
    }
}

int calc(int s, ll ban, int a, int b, int who) {
    ll msk = 0ll;
    dfs(a, msk, ban);
    dfs(b, msk, ban);
    for (int i = 0; i < s * s; i++) {
        if ((msk >> i) & 1) continue;
        ban |= (1ll << i);
    }
    if (ok[s][a][b][who].count(ban)) {
        return ok[s][a][b][who][ban];
    }
    if (!can_move(ban, a) && !can_move(ban, b)) {
        return 0;
    } else {
        if (who == 0) {
            if (can_move(ban, a)) {
                int score = -1e9;
                for (int x : g[a]) {
                    if ((ban >> x) & 1) continue;
                    ll go = ban | (1ll << x);
                    score = max(score, calc(s, go, x, b, 1) + 1);
                }
                return ok[s][a][b][who][ban] = score;
            } else {
                return ok[s][a][b][who][ban] = calc(s, ban, a, b, 1);
            }
        } else {
            if (can_move(ban, b)) {
                int score = 1e9;
                for (int x : g[b]) {
                    if ((ban >> x) & 1) continue;
                    ll go = ban | (1ll << x);
                    score = min(score, calc(s, go, a, x, 0) - 1);
                }
                return ok[s][a][b][who][ban] = score;
            } else {
                return ok[s][a][b][who][ban] = calc(s, ban, a, b, 0);
            }
        }
    }
}

void runTestCase(int const testCaseNumber) {
    int s, ra, pa, rb, pb, c;
    my_cin >> s >> ra >> pa >> rb >> pb >> c;
    ra--, pa--, rb--, pb--;
    for (int i = 0; i < s * s; i++) g[i].clear();
    int ptr = 0;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            id[i][j] = ptr++;
        }
    }
    auto add_edge = [&](int ra, int pa, int rb, int pb) {
        int u = id[ra][pa], v = id[rb][pb];
        g[u].push_back(v);
        g[v].push_back(u);
    };
    for (int i = 0; i < s; i++) {
        for (int j = 1; j < 2 * i + 1; j++) {
            add_edge(i, j, i, j - 1);
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            if (i + 1 < s && j % 2 == 0) {
                add_edge(i, j, i + 1, j + 1);
            }
        }
    }
    ll ban = 0;
    for (int i = 0; i < c; i++) {
        int r, p;
        my_cin >> r >> p;
        r--, p--;
        ban |= (1ll << id[r][p]);
    }
    int a = id[ra][pa], b = id[rb][pb];
    ban |= (1ll << a);
    ban |= (1ll << b);
    my_cout << "Case #" << testCaseNumber << ": " << calc(s, ban, a, b, 0) << "\n";
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
}  // namespace KickStart_2020_RoundF_P3_PaintersDuel
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

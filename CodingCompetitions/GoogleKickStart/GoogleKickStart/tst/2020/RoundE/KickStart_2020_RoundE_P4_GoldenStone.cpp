// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundE_P4_GoldenStone.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundE_P4_GoldenStone {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using ll = long long;
const ll INF = 1000000000000;
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define trav(a, x) for (auto& a : x)
template <class T>
bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}

void runTestCase(int const testCaseNumber) {
    int N, M, S, R;
    my_cin >> N >> M >> S >> R;
    vector<vector<int>> graph(N);
    F0R(i, M) {
        int A, B;
        my_cin >> A >> B;
        A--;
        B--;
        graph[A].push_back(B);
        graph[B].push_back(A);
    }

    ll dist[N][N];
    F0R(r, N) {
        F0R(i, N) dist[r][r] = INF;
        dist[r][r] = 0;
        queue<int> q;
        q.push(r);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            trav(a, graph[cur]) {
                if (dist[r][cur] + 1 < dist[r][a]) {
                    dist[r][a] = dist[r][cur];
                    q.push(a);
                }
            }
        }
    }

    ll cost[N][S];
    F0R(i, N) F0R(j, S) cost[i][j] = INF;
    priority_queue<pair<ll, pair<int, int>>> q;
    F0R(i, N) {
        int C;
        my_cin >> C;
        while (C--) {
            int X;
            my_cin >> X;
            X--;
            cost[i][X] = 0;
            q.push({0, {i, X}});
        }
    }

    vector<int> in[R];
    int out[R];
    F0R(i, R) {
        int K;
        my_cin >> K;
        while (K--) {
            int X;
            my_cin >> X;
            X--;
            in[i].push_back(X);
        }
        my_cin >> out[i];
        out[i]--;
    }

    bool vis[N][S];
    F0R(i, N) F0R(j, S) vis[i][j] = false;
    while (!q.empty()) {
        int p = q.top().second.first;
        int x = q.top().second.second;
        q.pop();
        if (vis[p][x]) continue;
        vis[p][x] = true;
        ckmin(cost[p][x], INF);
        trav(a, graph[p]) {
            if (cost[p][x] + 1 < cost[a][x]) {
                cost[a][x] = cost[p][x] + 1;
                q.push({-cost[a][x], {a, x}});
            }
        }
        F0R(i, R) {
            if (vis[p][out[i]]) continue;
            ll sum = 0;
            trav(a, in[i]) sum += cost[p][a];
            if (sum < cost[p][out[i]]) {
                cost[p][out[i]] = sum;
                q.push({-sum, {p, out[i]}});
            }
        }
    }

    ll ans = INF;
    F0R(i, N) ckmin(ans, cost[i][0]);

    my_cout << "Case #" << testCaseNumber << ": " << (ans == INF ? -1 : ans) << '\n';
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
}  // namespace KickStart_2020_RoundE_P4_GoldenStone
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

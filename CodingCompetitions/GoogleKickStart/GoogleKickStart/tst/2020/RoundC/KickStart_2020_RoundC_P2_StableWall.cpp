// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundC_P2_StableWall.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstring>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundC_P2_StableWall
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

const int mxN=30;
int n, m;
string s[mxN], ans;
vector<int> adj[26];
bool bad;
bool vis[26], act[26];

void dfs(int u) {
    act[u]=1;
    vis[u]=1;
    for(int v : adj[u]) {
        if(act[v]&&v^u)
            bad=1;
        else {
            if(!vis[v])
                dfs(v);
        }
    }
    act[u]=0;
    ans+=(char)(u+'A');
}

void runTestCase(unsigned int const testCaseNumber)
{
    my_cin >> n >> m;
    set<char> t;
    for(int i=0; i<n; ++i) {
        my_cin >> s[i];
        for(char c : s[i])
            t.insert(c);
        if(i) {
            for(int j=0; j<m; ++j)
                adj[s[i-1][j]-'A'].push_back(s[i][j]-'A');
        }
    }
    memset(vis, 0, 26);
    memset(act, 0, 26);
    ans="";
    bad=0;
    for(char c : t)
        if(!vis[c-'A'])
            dfs(c-'A');
    if(bad)
        ans="-1";
    my_cout << "Case #" << testCaseNumber << ": " << ans << '\n';

    for(int i=0; i<26; ++i)
        adj[i].clear();
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



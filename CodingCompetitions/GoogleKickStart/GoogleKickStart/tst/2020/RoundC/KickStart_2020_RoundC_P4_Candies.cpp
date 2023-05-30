// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundC_P4_Candies.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundC_P4_Candies {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

#define ll long long
#define ar array

const int mxN = 2e5;
int n, q;
ll a[mxN];

struct ft {
    ll a[mxN + 1];
    void upd(int i, ll x) {
        for (++i; i <= n; i += i & -i) a[i] += x;
    }
    ll qry(int i) {
        ll r = 0;
        for (; i; i -= i & -i) r += a[i];
        return r;
    }
} f0[2], f1[2];

void app(int i, ll x) {
    f0[i & 1].upd(i, x - a[i]);
    f1[i & 1].upd(i, i * (x - a[i]));
    f0[i & 1 ^ 1].upd(i, -(x - a[i]));
    f1[i & 1 ^ 1].upd(i, -i * (x - a[i]));
    a[i] = x;
}

void runTestCase(int const testCaseNumber) {
    my_cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        ll a;
        my_cin >> a;
        app(i, a);
    }
    ll ans = 0;
    while (q--) {
        char qt;
        my_cin >> qt;
        if (qt == 'Q') {
            int l, r;
            my_cin >> l >> r, --l, --r;
            ll s = f1[l & 1].qry(r + 1) - f1[l & 1].qry(l) - (l - 1) * (f0[l & 1].qry(r + 1) - f0[l & 1].qry(l));
            ans += s;
            // cout << s << "\n";
        } else {
            int i, x;
            my_cin >> i >> x, --i;
            app(i, x);
        }
    }
    for (int i = 0; i < n; ++i) app(i, 0);
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
}  // namespace KickStart_2020_RoundC_P4_Candies
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundF_P4_Yeetzhee.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundF_P4_Yeetzhee
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using ll=long long;

vector <int> need;
int n, m;

bool in(vector <int> a) {
  if (a.size() > need.size()) return false;
  int ptr = (int) need.size() - (int) a.size();
  for (int i = 0; i < (int) a.size(); i++) {
    if (ptr == (int) need.size()) return true;
    if (a[i] <= need[ptr]) {
      ptr++;
    }
  }
  return (ptr == (int) need.size());
}

map <vector <int>, double> mp;
double iv;

double ans(vector <int> a, int tot) {
  sort(a.begin(), a.end());
  if (!in(a)) {
    return 1e18;
  }
  if (mp.count(a)) return mp[a];
  if (tot == n) {
    return 0;
  } else {
    vector <pair <int, double> > go;
    for (int i = 0; i < (int) a.size(); i++) {
      a[i]++;
      double ret = ans(a, tot + 1);
      go.push_back({1, ret});
      a[i]--;
    }
    if ((int) a.size() != m) {
      auto b = a;
      b.insert(b.begin(), 1);
      go.push_back({m - (int) a.size(), ans(b, tot + 1)});
    }
    auto check = [&] (double x) {
      double sum = 1;
      for (auto c : go) {
        sum += min(c.second, x) * c.first / m;
      }
      return sum <= x;
    };
    double sum = 1;
    for (auto c : go) sum += c.second * c.first / m;
    double vl = 0, vr = sum;
    int it = 100;
    while (it--) {
      double vm = (vl + vr) / 2;
      if (check(vm)) vr = vm;
      else vl = vm;
    }
    return mp[a] = vr;
  }
}

void runTestCase(unsigned int const testCaseNumber)
{
    mp.clear();
    my_cin >> n >> m;
    iv = 1 / (double) m;
    int k;
    my_cin >> k;
    need.resize(k);
    for (int i = 0; i < k; i++) my_cin >> need[i];
    sort(need.begin(), need.end());
    vector <int> go;
    my_cout.precision(10);
    my_cout << "Case #" << testCaseNumber << ": " << fixed  << ans(go, 0) <<  '\n';
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



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
namespace KickStart_2019_PracticeRound_P3_KickstartAlarm
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using ll = long long;

const ll MOD = 1000000007;

ll getPow(ll a,ll p){
  ll ret = 1,cp = a;
  while(p){
    if(p&1) ret = (ret*cp)%MOD;
    p >>= 1;
    cp = (cp*cp)%MOD;
  }
  return ret;
}

ll getK(ll i,ll k){
  if(i == 1) return k%MOD;
  ll ret = ((i*(getPow(i,k)-1)%MOD)*getPow(i-1,MOD-2))%MOD;
  return ret;
}

void runTestCase(unsigned int const testCaseNumber)
{
    ll N,K,x1,y1,C,D,E1,E2,F;
    my_cin >> N >> K >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
    vector<ll> A(N);
    A[0] = (x1+y1)%F;
    ll CD = C+D,E = E1+E2;
    for(ll i = 1; i < N; ++i) A[i] = (CD*A[i-1]+E)%F;
    ll psum = 0,nb = 1,kval = N,ret = 0;
    for(ll i = N-1; i >= 0; --i){
      psum = (psum+nb*A[i])%MOD;
      ++nb;
      ret = (ret+psum*getK(kval,K))%MOD;
      --kval;
    }
    my_cout << "Case #" << testCaseNumber << ": " << ret << '\n';
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



// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2020_RoundD_P4_LockedDoors.hpp"
#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2020_RoundD_P4_LockedDoors
{
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

struct UnionFind{
    long long num;
    vector<long long> rs,ps;
    UnionFind(){}
    UnionFind(long long n):num(n),rs(n,1),ps(n,0){iota(ps.begin(),ps.end(),0);}
    long long find(long long x){
        return (x==ps[x]?x:ps[x]=find(ps[x]));
    }
    bool same(long long x,long long y){
        return find(x)==find(y);
    }
    void unite(long long x,long long y){
        x=find(x);y=find(y);
        if(x==y) return;
        if(rs[x]<rs[y]) swap(x,y);
        rs[x]+=rs[y];
        ps[y]=x;
        num--;
    }
    long long size(long long x){
        return rs[find(x)];
    }
    long long count() const{
        return num;
    }
};

void runTestCase(unsigned int const testCaseNumber)
{
    long long n,q;
    my_cin>>n>>q;
    vector<long long> ds(n-1);
    for(long long i=0;i<n-1;i++) my_cin>>ds[i];

    vector<long long> ss(q),ks(q);
    for(long long i=0;i<q;i++) my_cin>>ss[i]>>ks[i],ss[i]--;

    using P = pair<long long, long long>;
    vector<P> vp;
    for(long long i=0;i<n-1;i++)
        vp.emplace_back(ds[i],i);
    sort(vp.begin(),vp.end());

    vector<long long> ord(n-1);
    for(long long i=0;i<n-1;i++)
        ord[i]=vp[i].second;

    // check(ls[i]) = false
    // check(rs[i]) = true
    vector<long long> ls(q,-1),rs(q,n-1);
    while(1){
        long long flg=0;
        vector<vector<long long>> G(n);
        for(long long i=0;i<q;i++){
            if(ls[i]+1<rs[i]){
                long long mid=(ls[i]+rs[i])>>1;
                G[mid].emplace_back(i);
                flg=1;
            }
        }
        if(!flg) break;
        UnionFind uf(n);
        for(long long i=0;i<n-1;i++){
            uf.unite(ord[i],ord[i]+1);
            for(long long k:G[i]){
                if(uf.size(ss[k])>=ks[k]) rs[k]=i;
                else ls[k]=i;
            }
        }
    }

    vector<long long> ans(q);
    vector<vector<long long>> G(n+1);
    for(long long i=0;i<q;i++){
        assert(rs[i]<n-1);
        if(ks[i]==1){
            ans[i]=ss[i];
        }else{
            G[rs[i]].emplace_back(i);
        }
    }

    UnionFind uf(n);
    for(long long i=0;i<n-1;i++){
        // [xL, xR] [yL, yR]
        long long xR=ord[i];
        long long xL=xR-(uf.size(xR)-1);
        assert(uf.same(xL,xR));

        long long yL=ord[i]+1;
        long long yR=yL+(uf.size(yL)-1);
        assert(uf.same(yL,yR));

        for(long long k:G[i]){
            assert(uf.size(ss[k])<ks[k]);
            if(uf.same(xL,ss[k])){
                ans[k]=yL+(ks[k]-(uf.size(ss[k])+1));
            }else{
                ans[k]=xR-(ks[k]-(uf.size(ss[k])+1));
            }
        }
        uf.unite(ord[i],ord[i]+1);
    }

    my_cout << "Case #" << testCaseNumber << ":";
    for(long long i=0;i<q;i++) my_cout<<' '<<ans[i]+1;
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
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~



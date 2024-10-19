#ifdef LOCAL

#include "debug.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define debug(...)
#define debugArr(...)

#endif


using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = pair<int,int>;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int mod=998244353;
constexpr int inf=1000000000;
constexpr ll MOD=998244353;
constexpr ll INF=1000000000000000000ll;
#define fastio ios_base::sync_with_stdio(false);cin.tie(nullptr)
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define all(x) (x).begin(),(x).end()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rngll(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
T randint(T __L, T __R) {return uniform_int_distribution<T>(__L,__R)(rngll);}

ll ipow(ll _a,ll _b){_a %= MOD;ll _ret=1;while(_b){if(_b&1) _ret=_ret*_a % MOD;_a=_a*_a % MOD;_b>>=1;}return _ret;}
ll ipowM(ll _a,ll _b,ll _MM){_a %= _MM;ll _ret=1%_MM;while(_b){if(_b&1) _ret=_ret*_a % _MM;_a=_a*_a % _MM;_b>>=1;}return _ret;}



// x: dp 초기값
// ret: 선형 점화식 계수, return 되는 벡터
// dp[n]=ret[0]*dp[n-1]+ ... + ret[m-1]*dp[n-m]
vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		ll t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		ll k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}

int main(){
	int n;
	cin>>n;
	vector<int> T;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		T.pb(x);
	}
	vector<int> ans = berlekamp_massey(T);
	cout<<ans.size()<<endl;
	for(int i:ans)cout<<i<<" ";
}
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

constexpr int mod=1000000007;
constexpr int inf=1000000000;
constexpr ll MOD=1000000007ll;
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


int main(){
	
	return 0;
}


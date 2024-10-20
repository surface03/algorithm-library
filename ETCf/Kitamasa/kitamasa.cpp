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

constexpr int mod=1999;
constexpr int inf=1000000000;
constexpr ll MOD=1999;
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

// https://koosaga.com/231
// https://cubelover.tistory.com/21

// Source: https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4
// I made some minor adjustments to the original source to fit my style.


// 키타마사법
// dp[0], dp[1], ..., dp[m-1] : 각 dp의 초기항
// rec[0], rec[1], ..., rec[m-1]: 선형 점화식 계수
// dp[i]=rec[0]*dp[i-1] + rec[1]*dp[i-2] + ... + rec[m-1]*dp[i-m]
// dp[n] 반환
// 오버플로우 조심 (mod*2 <= INT_MAX인 경우는 정상 작동)
int kitamasa(vector<int> rec, vector<int> dp, ll n){
	int m = rec.size();
	if(n <= m-1) return dp[n] % mod;

	vector<int> s(m), t(m);
	s[0] = 1;

	if(m <= 1) t[0] = rec[0];
	else t[1] = 1;

	// 다항식 v, 다항식 w
	// v * w   mod (x^m-rec[0]*x^(m-1)- ... - rec[m-1]*x^0) 반환
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		// 다항식 곱
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		// 다항식 나머지
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};

	// x^n mod p 계산
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}

	// 계수 계산
	int ret = 0;
	for(int i=0; i<m; i++){
		ret += 1ll * s[i] * dp[i] % mod;
		if(ret >= mod) ret -= mod;
	}
	return ret;
}


int main(){
	
}


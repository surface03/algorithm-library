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

// sum f(1...N)을 O(N^(2/3))에 구하기
// f, g는 multiplicative
// 아래 코드는 f=phi, g=1
const int MAXN = 2000000;
ll phi_sum[MAXN + 10];
unordered_map<ll,ll> mp;
vector<int> prime;
bool not_prime[MAXN + 10];

ll Sum(ll x){
    if(x<=MAXN)return phi_sum[x];
    auto t=mp.find(x);
    if(t!=mp.end())return t->se;
    ll ans=x%MOD*(x+1)%MOD*ipow(2,MOD-2)%MOD; //s_f*g(x)
    for(ll i=2,j;i<=x;i=j+1){
        j=x/(x/i);
        ans=(ans+Sum(x/i)*(j-i+1)%MOD*(MOD-1))%MOD; //-s_f(x/i)*(g(i)+...+g(j))
    }
    // g(1)로 나누는 과정 생략

    return mp[x]=ans%MOD;
}

int main(){
	phi_sum[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (!not_prime[i]) {
            prime.push_back(i);

            // i가 소수일 때 값 대입
            phi_sum[i] = i - 1;
        }
        for (int j = 0; j < (int)prime.size() && 1ll*i * prime[j] <= 1ll*MAXN; ++j) {
            not_prime[i * prime[j]] = true;

            if (i % prime[j] == 0) {
                // i가 prime[j]의 배수인 경우 대입
                phi_sum[i * prime[j]] = phi_sum[i] * prime[j];
                break;
            } else {
                // i가 prime[j]의 배수가 아닌 경우 대입
                phi_sum[i * prime[j]] = phi_sum[i] * phi_sum[prime[j]];
            }
        }
    }
    for(int i=2;i<=MAXN;i++)phi_sum[i]=(phi_sum[i]+phi_sum[i-1])%MOD;
	ll N;
	cin>>N;
	cout<<Sum(N)<<"\n";
	return 0;
}


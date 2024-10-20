/**
 * Xudyh's sieve
 * 
 * Calculates sum f(1...N)
 * f, g is multiplicative function
 * Example is f=phi, g=1
 * 
 * O(N^(2/3))
 */

const int MAXN = 2000000;
ll phi_sum[MAXN + 10];
unordered_map<ll,ll> mp;
vector<int> prime;
bool not_prime[MAXN + 10];

// Calculates sum f(1...N)
ll Sum(ll x){
	if(x<=MAXN)return phi_sum[x];
	auto t=mp.find(x);
	if(t!=mp.end())return t->se;
	ll ans=x%MOD*(x+1)%MOD*ipow(2,MOD-2)%MOD; //sum f*g(1...x)
	for(ll i=2,j;i<=x;i=j+1){
		j=x/(x/i);
		ans=(ans+Sum(x/i)*(j-i+1)%MOD*(MOD-1))%MOD; //-(sum f(1...x/i)) * (g(i)+...+g(j))
	}
	// g(1)로 나누는 과정 생략

	return mp[x]=ans%MOD;
}

void preprocess(){
	// Calculate phi_sum[1...MAXN] here
}

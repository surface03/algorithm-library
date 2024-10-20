/**
 * MilerRabin, PollardRho
 * 
 * For Prime test, Factorization
 * 
 * is_prime(N): Checks if N is prime
 * Factorization(N): Returns sorted prime factorization of N
 * 
 * Original Code: https://github.com/rkm0959/Number_Theory_in_CP_PS/blob/main/6. Miller-Rabin 소수 판별 알고리즘과 Pollard-Rho 소인수분해/BOJ_4149.cpp
 * Reference: https://rkm0959.tistory.com/183
 */

// returns x*y % mod
// Overflow control
ll big_mul(ll _a, ll _b, ll _mod){return (ll)((__int128)_a*_b%_mod); }

// N - 1 = 2^s * d, r = 0,1,...,s-1
// Checks a^d = 1 (mod N), a^(2^r*d)=-1 (mod N)
bool MilerRabin_attempt(ll N, ll a){
	auto big_pow = [](ll _a, ll _b, ll _mod){
		ll ret = 1;
		while(_b){
			if (_b&1) ret=big_mul(ret,_a,_mod);
			_b>>=1;
			_a=big_mul(_a,_a,_mod);
		}
		return ret%_mod;
	};
	if(N%a==0) return false;
	ll s=0, d=N-1;
	while(d%2==0){
		d/=2;
		s++;
	}
	ll p=big_pow(a,d,N);
	if(p==1||p==N-1) return true;
	s--;
	while(s--){
		p=big_mul(p,p,N);
		if(p==N-1) return true;
	}
	return false;
}

// Check if N is Prime
// O(logN)
bool is_prime(ll N){
	if(N==1) return false;
	ll tc_prime[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	for(int i=0;i<12;i++){
		if(N==tc_prime[i]) return true;
		if(N<tc_prime[i]) return false;
		if(N>40 && !MilerRabin_attempt(N,tc_prime[i])) return false;
	}
	return (N<=40)?false:true;
}

ll PollardRho(ll N){
	auto Map = [](ll val, ll c, ll N) {
		val=big_mul(val,val,N)+c;
		if(val >= N) val -= N;
		return val;
	};

	// For better randomization, take 2 <= x < N
	ll x=rng()%(N-2)+2, y=x;
	// take 1 <= c < N
	ll c=rng()%(N-1)+1;

	while(1){
		x=Map(x,c,N);
		y=Map(y=Map(y,c,N),c,N);
		ll g=gcd(x-y,N);
		if(g==1) continue;
		if(!is_prime(g))return PollardRho(g);
		else return g;
	}
}

// Return the prime factorization of N
// O(N^(1/4))
vector<ll> Factorization(ll N){
	vector<ll> ret;
	while(N%2==0) {
		ret.push_back(2);
		N/=2;
	}
	while(N!=1 && !is_prime(N)){
		ll d=PollardRho(N);
		while(N%d==0) {
			ret.push_back(d);
			N/=d;
		}
	}
	if(N!=1) ret.push_back(N);
	sort(ret.begin(), ret.end());
	return ret;
}

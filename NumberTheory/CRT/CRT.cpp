/**
 * Chinese Remainder Theorem
 * Original Code: https://github.com/Pentagon03/Algorithms/tree/master/Math
 * Reference: https://rkm0959.tistory.com/180
 * I changed it to match my coding style.
 * 
 * 
 * In the case of mod M, always ensure that the input satisfies 0 <= input < M
 * 
 * ext_gcd(a, b): returns {g, x, y} that a*x + b*y = g = gcd(a,b)
 * inv(a, m): returns a^-1 mod m
 * crt_merge(c1, c2): merges two congruences
 * crt(v): merges every congruences in vector v and returns answer
 * solve(a, b, c): solves ax = b (mod c), returns the answer as congruence
 */


// returns {g, x, y} that a*x + b*y = g = gcd(a,b)
struct tll{ll g, x, y;};
tll ext_gcd(ll a, ll b) { // works when a<0 or b<0
	if(!b) return tll{a, 1, 0};
	auto[g,x,y] = ext_gcd(b, a%b);
	return tll{g, y, x-a/b*y};
}

// returns x that a*x = 1 mod m
// returns -1 when there is no inverse
ll inv(ll a, ll m){
	auto [g,x,y] = ext_gcd(a, m);
	if(g != 1) return -1;
	return (x%m + m) % m;
}

// 항상 0 <= a < m 를 만족하도록 입력을 넣자.
struct cong{ll a, m;}; // a mod m

cong crt_merge(const cong &c1, const cong &c2){
	auto[xa, xm] = c1; auto[ya, ym] = c2;
	auto [g,x,y] = ext_gcd(xm, ym);
	if((ya-xa) % g != 0) return cong{-1,0};
	auto ga = (ya-xa)/g;
	auto yt = ym / g;
	x = (x * ga % yt + yt) % yt;
	return cong{xm * x + xa, xm * yt};
}

// When no answer, returns cong{-1, 0}
cong crt(const vector<cong> &cong_v) {
	auto ans = cong{0,1};
	for(const auto&cg: cong_v){
		ans = crt_merge(ans, cg);
		if(ans.m == 0)return ans;
	}
	return ans;
}

// When no answer, returns cong{-1, 0}
cong solve(ll a, ll b, ll c) {
	ll g = gcd(a, c);
	if(b%g!=0) return cong{-1, 0};
	a/=g; b/=g; c/=g;
	ll sol = inv(a,c)*b%c;
	return cong{sol, c};
}

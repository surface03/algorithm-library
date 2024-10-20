/**
 * Calculating Extended Euclidean Algorithmm, Modulo Inverse
 * 
 * Original Code: https://github.com/Pentagon03/Algorithms/blob/master/Math/ext_gcd%26inv.cpp
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

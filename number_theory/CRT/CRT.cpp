// CRT
// Original Code: https://github.com/Pentagon03/Algorithms/tree/master/Math
// Reference: https://rkm0959.tistory.com/180
// I changed it to match my coding style.


/*
ext gcd
returns {g, x, y} that a * x + b * y = g = gcd(a,b)
*/

struct tll{ll g, x, y;};
tll ext_gcd(ll a, ll b) { // works when a<0 or b<0
    if(!b) return tll{a, 1, 0};
    auto[g,x,y] = ext_gcd(b, a%b);
    return tll{g, y, x-a/b*y};
}

// (x%m + m) % m == x mod m, works also when x is negative
// return x that a * x = 1 mod m
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

// 답이 없는 경우 cong{-1, 0} 반환
cong crt(const vector<cong> &cong_v) {
    auto ans = cong{0,1};
    for(const auto&cg: cong_v){
        ans = crt_merge(ans, cg);
        if(ans.m == 0)return ans;
    }
    return ans;
}
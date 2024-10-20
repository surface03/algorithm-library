#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pii=pair<int,int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
	while(1){
		ll a,b;
		scanf("%lld %lld",&a,&b);
		if(a==-123)break;
		// a~b 사이 난수 생성 (long long 범위)
		ll nx=uniform_int_distribution<ll>(a,b)(rng);

		printf("%lld\n", nx);
	}
}
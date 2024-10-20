#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pii=pair<int,int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
	while(1){
		int a,b;
		scanf("%d %d",&a,&b);
		if(a==-123)break;
		// a~b 사이 난수 생성 (int 범위)
		int nx=uniform_int_distribution<int>(a,b)(rng);

		printf("%d\n", nx);
	}
}
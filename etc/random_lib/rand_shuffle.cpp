#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int p[200];

int main(){
	for(int i=0;i<100;i++){
		p[i]=i+1;
	}
	// mt19937을 이용한 랜덤 셔플
	shuffle(p, p+100, rng);
	for(int i=0;i<100;i++){
		printf("%d\n", p[i]);
	}
}
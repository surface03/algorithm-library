#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pii=pair<int,int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
	int n;
	scanf("%d",&n);
	uniform_int_distribution<int> dis(1,n);
	for(int i=0;i<20;i++){
		// 1~n 사이 난수 생성
		int nx=dis(rng);
		cout << nx << endl;
	}
}
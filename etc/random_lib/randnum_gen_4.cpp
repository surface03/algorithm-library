#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pii=pair<int,int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
	for(int i=0;i<20;i++){
		// unsigned int 범위 난수 생성
		cout << rng() << endl;
	}
}
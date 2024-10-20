#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;


int main(){
	srand((int)time(NULL));
	while(1){
		// 0~RAND_MAX 사이 난수 생성
		int x=rand();
		cout << x << endl;
		if(x == 0 || x == RAND_MAX) break;
	}
}
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;


vector<int> prime;
bool notprime[50000010];
int mobius[50000010];
unordered_map<int, ll> mp;

ll SQRT(ll x){
	ll sq=sqrt(x)+1;
	while(sq*sq>x)sq--;
	return sq;
}

ll Smob(int x){
	if(x<=50000000)return mobius[x];
	//if(x<=0)return 0;
	auto TT=mp.find(x);
	if(TT!=mp.end())return TT->se;
	ll ans=1;
	for(ll i=2,j;i<=x;i=j+1){
		j=x/(x/i);
		ans-=Smob(x/i)*(j-i+1);
	}
	return mp[x]=ans;
}

ll cnt(ll x){
	ll ret=0;
	ll xsq=SQRT(x);
	ll t=min(1000000ll,xsq);
	for(ll i=1;i<=t;i++){
		ret+=(x/(i*i))*(mobius[i]-mobius[i-1]);
	}
	for(ll i=t+1,j;i<=xsq;i=j+1){
		j=(ll)SQRT(x/(x/(i*i)));
		ret+=(x/(i*i))*(Smob(j)-Smob(i-1));
	}
	return ret;
}
int main(){
	mobius[1]=1;
	for(ll i=2;i<=50000000ll;i++){
		if(!notprime[i]){
			prime.push_back(i);
			mobius[i]=-1;
		}
		for(ll j=0;j<(int)prime.size()&&i*prime[j]<50000000ll;j++){
			notprime[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
			else{
				mobius[i*prime[j]]=-mobius[i];
			}
		}
	}
	for(ll i=2;i<=50000000ll;i++){
		mobius[i]+=mobius[i-1];
	}
	ll K;
	cin>>K;
	cout<<cnt(K)<<endl;
}
/**
 * Segment Tree with Lazy Propagation
 * 
 * Range update: a[i] <- gop*a[i]+pl
 * Range query: sum(a[i])
 */


const ll MOD = 998244353;
const int MAXN = 500050;

struct LazySeg{
	int N;
	ll tree[4*MAXN],lazy[4*MAXN][2];
	vector<ll> a;

	LazySeg(){}

	LazySeg(int _N){
		N = _N;

		for(int i=0;i<=4*N;i++){
			lazy[i][0]=1,lazy[i][1]=0;
			tree[i]=0;
		}

		a.clear();
	}

	LazySeg(int _N, vector<ll> _a){
		N = _N;

		for(int i=0;i<=4*N;i++){
			lazy[i][0]=1,lazy[i][1]=0;
			tree[i]=0;
		}

		a = _a;
		build(1,1,N);
	}

	void build(int now,int s,int e){
		if(s==e){
			tree[now]=a[s-1];
			return;
		}
		int nl=now*2,nr=2*now+1,m=(s+e)/2;
		build(nl,s,m);
		build(nr,m+1,e);
		tree[now]=(tree[nl]+tree[nr])%MOD;
	}

	void propagate(int now,int s,int e){
		tree[now]=(tree[now]*lazy[now][0]+lazy[now][1]*(e-s+1))%MOD;
		if(s!=e){
			for(int i=now*2;i<=now*2+1;i++){
				lazy[i][0]=(lazy[i][0]*lazy[now][0])%MOD;
				lazy[i][1]=(lazy[now][1]+lazy[i][1]*lazy[now][0])%MOD;
			}
		}
		lazy[now][0]=1,lazy[now][1]=0;
	}

	// 구간 업데이트 a[i] <- gop*a[i]+pl
	void update(int now,int s,int e,int qs,int qe,ll gop,ll pl){
		propagate(now,s,e);
		if(e<qs||qe<s)return;
		if(qs<=s&&e<=qe){
			lazy[now][0]=(lazy[now][0]*gop)%MOD;
			lazy[now][1]=(lazy[now][1]*gop+pl)%MOD;
			propagate(now,s,e);
			return;
		}
		int nl=now*2,nr=2*now+1,m=(s+e)/2;
		update(nl,s,m,qs,qe,gop,pl);
		update(nr,m+1,e,qs,qe,gop,pl);
		tree[now]=(tree[nl]+tree[nr])%MOD;
	}

	// 구간 합
	ll query(int now,int s,int e,int qs,int qe){
		propagate(now,s,e);
		if(e<qs||qe<s)return 0;
		if(qs<=s&&e<=qe)return tree[now];
		int nl=now*2,nr=2*now+1,m=(s+e)/2;
		return (query(nl,s,m,qs,qe)+query(nr,m+1,e,qs,qe))%MOD;
	}

	void update(int s,int e,ll gop,ll pl){ update(1,1,N,s,e,gop,pl); }
	ll query(int s,int e){ return query(1,1,N,s,e); }
};

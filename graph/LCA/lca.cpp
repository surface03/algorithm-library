/**
 * Lowest Common Ancestor
 * 
 * Preprocessing O(NlogN), O(1) per query.
 * Index is 1-based
 */

const int MAXN = 500010;

struct LCA{
	ll dep[MAXN];
	vector<vector<pair<int,ll>>> tree;

	vector<int> ett;

	int N,in[MAXN],rein[2*MAXN+10],tcnt,idx[MAXN];
	int arr[2*MAXN+10][25];

	LCA(){}

	LCA(int _N): N(_N){
		for(int i=0;i<=_N;i++)dep[i]=0;
		for(int i=0;i<=2*_N+3;i++)rein[i]=0;
		tree.clear();
		tree.resize(_N+5);
		ett.clear();

		tcnt=0;
	}

	void dfs(int now,int p=-1){
		in[now]=++tcnt;

		ett.push_back(in[now]);
		idx[now]=SZ(ett)-1;
		rein[in[now]]=now;

		for(auto& [i,j]:tree[now]){
			if(i==p)continue;
			dep[i]=dep[now]+j;
			dfs(i,now);
			ett.push_back(in[now]);
		}
	}

	// insert edge {a, b} with cost w
	void append(int a,int b,ll w=1){
		tree[a].push_back({b,w});
		tree[b].push_back({a,w});
	}

	// LCA preprocessing with r as root node
	void gen_lca(int r){
		ett.clear();
		tcnt=0;
		dep[r]=0;
		dfs(r,-1);
		for(int i=0;i<SZ(ett);i++)arr[i][0]=ett[i];

		int lgN = 31-__builtin_clz(SZ(ett));
		for(int j=1;j<=lgN;j++){
			for(int k=0;k<=SZ(ett)-(1<<j);k++){
				arr[k][j]=min(arr[k][j-1],arr[k+(1<<(j-1))][j-1]);
			}
		}
	}

	// LCA of vertex a, b
	int lca(int a,int b){
		int L=idx[a], R=idx[b];
		if(L>R)swap(L,R);
		int pw=31-__builtin_clz(R-L+1);
		return rein[min(arr[L][pw],arr[R-(1<<pw)+1][pw])];
	}

	// Distance of vertex a, b
	int dist(int a,int b){
		return dep[a]+dep[b]-2*dep[lca(a,b)];
	}
};

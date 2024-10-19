using ui = unsigned int;

struct SegTree{
	int N;
	ui tree[2000010],lazy[2000010][2];

	SegTree(int _N = 500000){
		N=_N;
		for(int i=0;i<2000010;i++)lazy[i][0]=1,lazy[i][1]=0;
		memset(tree,0,sizeof tree);
	}
	void propagate(int now,int s,int e){
	    tree[now]=tree[now]*lazy[now][0] + lazy[now][1]*(e-s+1);
	    if(s!=e){
	        for(int i=now*2;i<=now*2+1;i++){
	            lazy[i][0]=lazy[i][0]*lazy[now][0];
	            lazy[i][1]=lazy[now][1]+lazy[i][1]*lazy[now][0];
	        }
	    }
	    lazy[now][0]=1,lazy[now][1]=0;
	}
	void update(int now,int s,int e,int qs,int qe,ui gop,ui pl){
	    propagate(now,s,e);
	    if(e<qs||qe<s)return;
	    if(qs<=s&&e<=qe){
	        lazy[now][0]=lazy[now][0]*gop;
	        lazy[now][1]=lazy[now][1]*gop+pl;
	        propagate(now,s,e);
	        return;
	    }
	    int nl=now*2,nr=2*now+1,m=(s+e)/2;
	    update(nl,s,m,qs,qe,gop,pl);
	    update(nr,m+1,e,qs,qe,gop,pl);
	    tree[now]=tree[nl]+tree[nr];
	}
	ui query(int now,int s,int e,int qs,int qe){
	    propagate(now,s,e);
	    if(e<qs||qe<s)return 0;
	    if(qs<=s&&e<=qe)return tree[now];
	    int nl=now*2,nr=2*now+1,m=(s+e)/2;
	    return query(nl,s,m,qs,qe)+query(nr,m+1,e,qs,qe);
	}

	
	ui query(int L,int R){
		return query(1,1,N,L,R);
	}
	void upd(int L,int R,ui gop,ui pl){
		update(1,1,N,L,R,gop,pl);
	}
}seg;

/**
 * HLD
 * Original Source: https://justicehui.github.io/hard-algorithm/2020/01/24/hld/
 * Modified code style
*/

/**
 * sz[i] = i를 루트로 하는 서브트리의 크기
 * dep[i] = i의 깊이
 * par[i] = i의 부모 정점
 * top[i] = i가 속한 체인의 가장 위에 있는 정점
 * in[i], out[i] = dfs ordering
 * g[i] = i의 자식 정점 (부모 정점 제거 필요, 양방향 간선 => 단방향 간선)
 * 
 * 루트 정점은 기본적으로 1번
 * 쿼리 및 업데이트는 교환법칙이 성립해야 한다.
 * 부모로 가는 간선이 입력으로 들어오지 않는다면 dfs0 삭제 가능
*/

const int MAXN = 500010;
int sz[MAXN], dep[MAXN], par[MAXN], _visited[MAXN];
int top[MAXN], in[MAXN], out[MAXN], tcnt;
vector<int> g[MAXN];

// g 계산
vector<int> g0[MAXN];
void dfs0(int now = 1){
	_visited[now] = 1;
	for(auto i : g0[now]){
		if(_visited[i]) continue;
		g[now].push_back(i);
		dfs0(i);
	}
}

// sz, dep, par 계산
// g[now][0] = now번 정점의 가장 큰 서브트리로 변환
void dfs1(int now = 1){
	sz[now]=1;
	for(auto &i : g[now]){
		dep[i]=dep[now] + 1;
		par[i]=now;
		dfs1(i);
		sz[now]+=sz[i];
		if(sz[i] > sz[g[now][0]]) swap(i, g[now][0]);
	}
}

// in, out 계산
void dfs2(int now = 1){
	in[now]=++tcnt;
	for(auto i : g[now]){
		top[i] = (i == g[now][0] ? top[now] : i);
		dfs2(i);
	}
	out[now]=tcnt;
}

// hld 초기화
void init_hld(int _N){
	/* tc 문제의 경우 sz, dep, par, 
	_visited, top, in, out, tcnt 초기화*/
	seg = SegTree(_N);
	dfs0(); dfs1(); dfs2();
}

// 경로 a~b에 업데이트
void upd_path(int a, int b, ui gop, ui pl){
    while(top[a] != top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        int st=top[a];
        seg.upd(in[st], in[a], gop, pl);
        a=par[st];
    }
    if(dep[a] > dep[b]) swap(a, b);
    seg.upd(in[a], in[b], gop, pl);
}

// a를 루트로 가지는 서브트리 업데이트
void upd_subtree(int a, ui gop, ui pl){
	seg.upd(in[a],out[a],gop,pl);
}

// 경로 a~b의 값 구하기
ui query_path(int a,int b){
	ui ret=0;
    while(top[a] != top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        int st=top[a];
        ret+=seg.query(in[st], in[a]);
        a=par[st];
    }
    if(dep[a] > dep[b]) swap(a, b);
    ret+=seg.query(in[a], in[b]);
    return ret;
}

// a를 루트로 가지는 서브트리 값 구하기
ui query_subtree(int a){
	return seg.query(in[a],out[a]);
}
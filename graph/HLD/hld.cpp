/**
 * Heavy Light Decomposition
 * 
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
 * 
 * 
 * Original Source: https://justicehui.github.io/hard-algorithm/2020/01/24/hld/
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
void upd_path(int a, int b, ll val){
	while(top[a] != top[b]){
		if(dep[top[a]] < dep[top[b]]) swap(a, b);
		int st=top[a];
		seg.upd(in[st], in[a], val);
		a=par[st];
	}
	if(dep[a] > dep[b]) swap(a, b);
	seg.upd(in[a], in[b], val);
}

// a를 루트로 가지는 서브트리 업데이트
void upd_subtree(int a, ll val){
	seg.upd(in[a],out[a],val);
}

// 경로 a~b의 값 구하기
ll query_path(int a,int b){
	ll ret=0;
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
ll query_subtree(int a){
	return seg.query(in[a],out[a]);
}

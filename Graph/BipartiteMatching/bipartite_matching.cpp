/**
 * Bipartite matching
 * 
 * 정점 번호는 1-based
 * 
 * 
 * 최대 이분 매칭 - 이분 그래프에서 각 정점이 최대 한번 선택되도록 간선 선택
 * 
 * max_match: 선택 가능한 최대 간선 수
 * N, M: group A, B의 최대 정점 개수 (번호는 1~N, 1~M)
 * g: group A -> group B의 간선
 * rev_g: group B -> group A의 간선
 * pv: 현재 pv번 dfs(flow)를 진행
 * vis: dfs(flow)시 방문 배열, pv로 체크
 * A[x]: group A의 x번 정점이 매칭된 group B의 정점
 * B[x]: group B의 x번 정점이 매칭된 group A의 정점
 * 
 * add_edge(x, y): group A의 x번 정점과 group B의 y번 정점을 연결
 * 
 * find_match(x, b):
 * 최대 매칭을 유지하면서,
 * b==0인 경우, group A의 x번 정점과 새로 매칭될 수 있는 group B 정점 찾기
 * b==1인 경우, group B의 x번 정점과 새로 매칭될 수 있는 group A 정점 찾기
 * 
 * gen_max_match(): 새로 최대 매칭을 계산
 * 
 * 
 * 
 * 최소 버텍스 커버 - 모든 간선에 대해, 양 끝점 중 적어도 하나의 정점이 포함되는 최소 정점 부분집합
 * get_min_vertex_cover: {groupA/B, vertex}
 * 
 * 
 * 최대독립집합 - 어떤 정점도 인접하지 않은 최대 정점 부분집합 (최소 버텍스 커버의 여집합)
 * get_max_independent_set: {groupA/B, vertex}
 * 
 * 
 * 쾨니그의 정리 - 이분 그래프에서 최대매칭 == 최소 버텍스 커버
 * 
 * 
 * Time Complexity:
 * find_match(): O(V+E)
 * gen_max_match(): O(VE)
 * get_min_vertex_cover: O(VE)
 * get_max_independent_set: O(VE)
 */

struct BipartiteMatching{
	int N,M;
	int max_match;
	vector<int> vis, A, B;
	vector<vector<int>> g, rev_g;
	int pv;

	BipartiteMatching(int _N,int _M)
		: N(_N), M(_M), max_match(0), vis(max(_N,_M)+1,0),
		A(_N+1), B(_M+1), g(_N+1), rev_g(_M+1), pv(0) {}

	void add_edge(int a,int b){
		g[a].push_back(b);
		rev_g[b].push_back(a);
	}

	bool dfs(int x, int b){
		vector<vector<int>>& adj = (b == 0) ? g : rev_g;
		vector<int>& U = (b == 0) ? A : B;
		vector<int>& V = (b == 0) ? B : A;

		for(int nx:adj[x]){
			if(vis[nx]!=pv && V[nx]<=0){
				vis[nx] = pv;
				U[x] = nx;
				V[nx] = x;
				return true;
			}
		}
		for(int nx:adj[x]){
			if(vis[nx]!=pv){
				vis[nx] = pv;
				if(dfs(V[nx], b)){
					U[x] = nx;
					V[nx] = x;
					return true;
				}
			}
		}
		return false;
	}

	void find_match(int x, int b){
		++pv;
		if(dfs(x, b)) ++max_match;
	}
	
	void gen_max_match(){
		pv = 0;
		vis.assign(max(N,M)+1, 0);
		max_match = 0;
		A.assign(N+1, 0);
		B.assign(M+1, 0);
		for(int i=1; i<=N; i++){
			++pv;
			if(dfs(i, 0)) ++max_match;
		}
	}

	vector<pii> get_min_vertex_cover(){
		if(pv == 0) max_matching();
		vector<vector<int>> g2(size(B));
		for(int i=0;i<size(A);i++){
			for(int x:g[i]){
				g2[x].push_back(i);
			}
		}
		vector<bool> chkA(size(A)), chkB(size(B));
		function<void(int,int)> dfs2 = [&](int x,int team){
			auto&chk = team?chkB:chkA;
			if(chk[x]) return;
			chk[x] = true;
			auto&rg = team?g2:g;
			for(int nx: rg[x])
				if((team == 0 && A[x] != nx) || (team == 1 && B[x] == nx))
					dfs2(nx, !team);
		};
		for(int i=0;i<size(A);i++)
			if(A[i] == -1)
				dfs2(i, 0);
		vector<pii> ans;
		for(int i=0;i<size(A);i++)
			if(!chkA[i])
				ans.emplace_back(0, i);
		for(int i=0;i<size(B);i++)
			if(chkB[i])
				ans.emplace_back(1, i);
		return ans;
	}
	vector<pii> get_max_independent_set(){
		auto mvc = get_min_vertex_cover();
		vector<bool> chkA(size(A)), chkB(size(B));
		for(auto[c,x]: mvc)
			(c?chkB:chkA)[x] = true;
		vector<pii> ans;
		for(int i=0;i<size(A);i++)
			if(!chkA[i])
				ans.emplace_back(0, i);
		for(int i=0;i<size(B);i++)
			if(!chkB[i])
				ans.emplace_back(1, i);
		return ans;
	}
};

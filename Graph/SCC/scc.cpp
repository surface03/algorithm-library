/**
 * Strongly Connected Component
 * 
 * generate_scc(N, g): Generates SCC using graph g, which contains N vertices
 * generate_scc_graph(): Generates SCC graph using SCC indices
 * 
 * 
 * Tarjan Algorithm
 * SCC indices are assigned in **reverse topological order**.
 * In other words, SCC 1 has no outgoing edges (outdegree = 0), and SCC N has no incoming edges (indegree = 0).
 */

const int MAXN = 500050;

struct SCC {
	// Internal variables (likely not to be used directly)
	stack<int> stk;
	int tcnt, dfsn[MAXN];


	// Number of vertices
	int N;

	// Number of SCC (Strongly Connected Components)
	int scc_cnt;

	// sccn[i]: The SCC index that vertex i belongs to
	int sccn[MAXN];

	// Original Graph
	vector<vector<int>> graph;

	// scc[i]: Vertices included in the i-th SCC
	vector<vector<int>> scc;

	// Graph constructed using SCC indices
	vector<vector<int>> scc_graph;

	SCC(){}

	SCC(int _N, vector<vector<int>>& g){
		generate_scc(_N, g);
	}

	void generate_scc(int _N, vector<vector<int>>& g){
		N = _N;
		tcnt = 0;
		scc_cnt = 0;
		while(!stk.empty()) stk.pop();
		for(int i=0; i<=N+5; i++){
			dfsn[i]=0;
			sccn[i]=0;
		}

		graph.clear();
		scc.clear();
		scc_graph.clear();

		graph = g;
		scc.push_back({});

		for(int i=1;i<=N;i++){
			if(!dfsn[i]) dfs(i);
		}
	}

	int dfs(int now){
		dfsn[now] = ++tcnt;
		int ret = dfsn[now];
		stk.push(now);
		for(int i: graph[now]){
			if(dfsn[i]==0)ret = min(ret,dfs(i));
			else if(sccn[i]==0)ret = min(ret,dfsn[i]); 
		}
		if(ret == dfsn[now]){
			scc_cnt++;
			vector<int> tmp;
			while(1){
				int t=stk.top();
				stk.pop();
				sccn[t]=scc_cnt;
				tmp.push_back(t);
				if(t==now)break;
			}
			scc.push_back(tmp);
		}
		return ret;
	}

	void generate_scc_graph(){
		scc_graph.clear();
		scc_graph.resize(N+5);

		for(int i=1;i<=N;i++){
			for(int j: graph[i]){
				if(sccn[i] == sccn[j])continue;
				scc_graph[ sccn[i] ].push_back(sccn[j]);
			}
		}

		for(int i=1;i<=scc_cnt;i++){
			sort(scc_graph[i].begin(), scc_graph[i].end());
			scc_graph[i].erase(unique(scc_graph[i].begin(), scc_graph[i].end()), scc_graph[i].end());
		}
	}
};

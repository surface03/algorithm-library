/**
 * Eulerian Trail (Directed/Undirected)
 * 
 * exists: 오일러 경로가 존재하는지
 * euler_vertex: 오일러 경로의 정점 순서 (v_0, v_1, ..., v_M)
 * euler_edge: 오일러 경로의 간선 순서 (e_0, e_1, ..., e_M-1)
 * 
 * 정점 번호는 0 이상 N-1 이하
 * 간선 번호는 입력되는 그래프 E의 인덱스로 결정
 * 
 * generate_euler_trail() 호출 시 exists, vertex, edge 계산
 * 
 * Original Code: https://judge.yosupo.jp/submission/193530 (jhnah917)
 */


struct DirectedEulerTrail{
    int N, M;
    vector<pair<int, int>> E;

    // exists: 오일러 경로가 존재하는지
    // euler_vertex: 오일러 경로의 정점 순서 (v_0, v_1, ..., v_M)
    // euler_edge: 오일러 경로의 간선 순서 (e_0, e_1, ..., e_M-1)
    bool exists;
    vector<int> euler_vertex;
    vector<int> euler_edge;

    vector<vector<int>> g;
    vector<int> in, out, path;

    DirectedEulerTrail() = default;

    DirectedEulerTrail(int _N, vector<pair<int,int>> _E){
        E = _E;
        N = _N;
        M = SZ(_E);

        generate_euler_trail();
    }

    void dfs(int v){
        while(!g[v].empty()){
            int x = g[v].back();
            g[v].pop_back();
            dfs(x);
        }
        path.push_back(v);
    }

    vector<int> get(){
        path.clear();
        for(int i=0; i<SZ(g); i++)
            if(in[i] < out[i]){
                dfs(i);
                return path;
            }

        for(int i=0; i<SZ(g); i++)
            if(out[i]){
                dfs(i);
                return path;
            }
        return path;
    }

    void generate_euler_trail(){
        exists = false;
        euler_vertex.clear();
        euler_edge.clear();

        M = SZ(E);
        if(M == 0){
            exists = true;
            euler_vertex.push_back(0);
            return;
        }

        g.clear(); in.clear(); out.clear();
        g.resize(N); in.resize(N); out.resize(N);
        for(auto [u,v] : E) g[u].push_back(v), out[u]++, in[v]++;

        auto R = get();
        if(SZ(R) != M + 1) return;

        reverse(R.begin(), R.end());
        map<pair<int,int>, vector<int>> X;
        int Mcnt = 0;

        // edge index label
        for(auto e : E) X[e].push_back(Mcnt++);

        vector<int> edges;
        for(int i=1; i<SZ(R); i++){
            auto &v = X[{R[i-1], R[i]}];
            if(v.empty()) return;
            edges.push_back(v.back());
            v.pop_back();
        }

        exists = true;
        euler_vertex = R;
        euler_edge = edges;
    }
};

struct UnDirectedEulerTrail{
    int N, M;
    vector<pair<int, int>> E;

    // exists: 오일러 경로가 존재하는지
    // euler_vertex: 오일러 경로의 정점 순서 (v_0, v_1, ..., v_M)
    // euler_edge: 오일러 경로의 간선 순서 (e_0, e_1, ..., e_M-1)
    bool exists;
    vector<int> euler_vertex;
    vector<int> euler_edge;


    vector<vector<pair<int,int>>> g;
    vector<int> deg, use, path;

    UnDirectedEulerTrail() = default;

    UnDirectedEulerTrail(int _N, vector<pair<int,int>> _E){
        E = _E;
        N = _N;
        M = SZ(_E);

        generate_euler_trail();
    }

    void dfs(int v){
        while(true){
            while(!g[v].empty() && use[g[v].back().second]) g[v].pop_back();
            if(g[v].empty()) break;

            auto [x,i] = g[v].back();
            g[v].pop_back();

            use[i] = 1;
            dfs(x);
        }
        path.push_back(v);
    }

    vector<int> get(){
        path.clear();
        fill(use.begin(), use.end(), 0);

        for(int i=0; i<SZ(g); i++)
            if(deg[i] % 2){
                dfs(i);
                return path;
            }

        for(int i=0; i<SZ(g); i++)
            if(deg[i]){
                dfs(i);
                return path;
            }
        return path;
    }

    void generate_euler_trail(){
        exists = false;
        euler_vertex.clear();
        euler_edge.clear();

        use.clear();
        use.resize(SZ(E));
        M = SZ(E);
        if(M == 0){
            exists = true;
            euler_vertex.push_back(0);
            return;
        }

        g.clear(); deg.clear(); use.clear();
        g.resize(N); deg.resize(N); use.resize(M);

        for(int i=0; i<M; i++){
            auto [u,v] = E[i];
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
            deg[u]++; deg[v]++;
        }

        auto R = get();
        if(SZ(R) != M + 1) return;

        reverse(R.begin(), R.end());
        map<pair<int,int>, vector<int>> X;
        int Mcnt = 0;

        for(auto [u,v] : E) X[{min(u,v),max(u,v)}].push_back(Mcnt++);

        vector<int> edges;
        for(int i=1; i<SZ(R); i++){
            auto &v = X[{min(R[i-1], R[i]), max(R[i-1], R[i])}];
            if(v.empty()) return;
            edges.push_back(v.back());
            v.pop_back();
        }

        exists = true;
        euler_vertex = R;
        euler_edge = edges;
    }
};

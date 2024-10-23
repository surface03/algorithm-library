/**
 * 2-satisfiability problem
 * 
 * N boolean variables
 * 
 * Checks if AND_{i=0 to sz-1}(CNF[i].first OR CNF[i].second) is satisfiable.
 * If satisfiable, returns {true, {x_1, x_2, ..., x_N}}
 * If not satisfiable, returns {false, {}}
 * 
 * The input must satisfy 1 <= abs(CNF[i].first) <= N
 * i represents the boolean variable x_i, and -i represents the boolean variable NOT x_i
 */
pair<bool, vector<int>> two_sat(int N, vector<pair<int,int>>& CNF){
	vector<vector<int>> input; input.resize(2*N+2);

	for(int i=0;i<(int)CNF.size();i++){
		int pp = CNF[i].fi>0 ? (CNF[i].fi<<1) : (-CNF[i].fi<<1)-1;
		int qq = CNF[i].se>0 ? (CNF[i].se<<1) : (-CNF[i].se<<1)-1;

		input[((pp-1)^1)+1].push_back(qq);
		input[((qq-1)^1)+1].push_back(pp);
	}

	SCC sc = SCC(2*N, input);
	vector<int> ret; ret.resize(N, 0);

	for(int i=2;i<=2*N;i+=2){
		if(sc.sccn[i-1] == sc.sccn[i]) return {false, {}};
		if(sc.sccn[i-1] > sc.sccn[i]) ret[i/2-1]=1;
	}
	return {true, ret};
}

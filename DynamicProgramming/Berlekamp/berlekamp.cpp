/**
 * Berlekamp Massey Algorithm
 * Original Code: https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4
 * 
 * Input x에 대해 가장 짧은 dp 점화식 생성
 * 각 input 및 output은 mod에 대한 나머지
 * 
 * Input x: dp 초기값
 * ret: 선형 점화식 계수, return 되는 벡터
 * dp[n]=ret[0]*dp[n-1]+ ... + ret[m-1]*dp[n-m]
 * 
 * O(SZ(x)^2)
 */

vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		ll t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		ll k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}

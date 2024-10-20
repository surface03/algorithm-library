/**
 * Kitamasa method
 * Original Code: https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4
 * Reference: https://koosaga.com/231
 * I made some minor adjustments to the original source to fit my style.
 * 
 * dp[0], dp[1], ..., dp[m-1] : 각 dp의 초기항
 * rec[0], rec[1], ..., rec[m-1]: 선형 점화식 계수
 * dp[i]=rec[0]*dp[i-1] + rec[1]*dp[i-2] + ... + rec[m-1]*dp[i-m]
 * dp[n] 반환
 * 오버플로우 조심 (mod*2 <= INT_MAX인 경우는 정상 작동)
 * 
 * O(SZ(rec)^2 * log n)
 */

int kitamasa(vector<int> rec, vector<int> dp, ll n){
	int m = rec.size();
	if(n <= m-1) return dp[n] % mod;

	vector<int> s(m), t(m);
	s[0] = 1;

	if(m <= 1) t[0] = rec[0];
	else t[1] = 1;

	// 다항식 v, 다항식 w
	// v * w   mod (x^m-rec[0]*x^(m-1)- ... - rec[m-1]*x^0) 반환
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		// 다항식 곱
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		// 다항식 나머지
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};

	// x^n mod p 계산
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}

	// 계수 계산
	int ret = 0;
	for(int i=0; i<m; i++){
		ret += 1ll * s[i] * dp[i] % mod;
		if(ret >= mod) ret -= mod;
	}
	return ret;
}

/**
 * Fast Determinant
 * 
 * Calculates determinant of matrix M (N*N matrix)
 * Destroys the input matrix M
 * Input matrix must follow 0 <= M[i][j] < _mod
 * Delete _mod to get pure determinant
 * Time Complexity: O(N^3) (When N = 500, 0.07 sec)
 * 
 * 
 * Original Code: https://github.com/kth-competitive-programming/kactl/tree/main/content/numerical
 * Modified from the original code
 */

//constexpr ll MOD = 1'000'000'007;

template <ll _mod = MOD>
ll fast_det(vector<vector<ll>>& a) {
	int N = SZ(a); ll ans = 1;
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			while (a[j][i] != 0) {
				ll t = a[i][i] / a[j][i];
				if(t) for(int k=i;k<N;k++) a[i][k] = (a[i][k] - a[j][k] * t) % _mod;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i] % _mod;
		if (!ans) return 0;
	}
	return (ans + _mod) % _mod;
}

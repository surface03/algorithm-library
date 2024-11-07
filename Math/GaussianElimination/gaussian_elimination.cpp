/**
 * Gaussian Elimination
 * 
 * Gets RREF, rank, Determinant, Inverse matrix
 * Solves linear system
 * 
 * If typename T is integer, all values are considered with MOD.
 * If typename T is floating-point type, comparisons with zero uses eps(=1e-9)
 * If typename T is user-defined type, the operators +, -, *, /, and type casting from int to T must be defined.
 * 
 * Can Modify IsZero, Add, Sub, Mul, Div if necessary.
 * 
 * 
 * Gaussian_Elimination(a):
 * Input a is N*M matrix.
 * returns {rref, rank, det, inv} of matrix a.
 * if do_inv is false, only calculates rref, rank.
 * Time Complexity: O(NM * min(N,M)) or O(NM * sqrt(NM))
 * 
 * 
 * solve_linear_system(A, b):
 * Input A is N*M matrix, b is vector with size N.
 * Solves Ax = b.
 * returns {R, c, {basis[0], basis[1], ..., basis[R-1]}}.
 * If Ax = b has no solution, R == -1.
 * return vector c, basis[i] is size M vector.
 * Ax = b <=> x = c + k1*basis[0] + k2*basis[1] + ... + kR*basis[R-1] for any ki
 * Time Complexity: O(NM * min(N,M)) or O(NM * sqrt(NM))
 * 
 * 
 * Original Code: https://judge.yosupo.jp/submission/202930
 * Modified to support user-defined typename T
 */


template <typename T>
inline bool IsZero(T x) {
	if constexpr (is_floating_point_v<T>) return std::abs(x) < 1e-9;
	else return x == T(0);
}

template <typename T>
inline T Add(T a, T b) {
	if constexpr (is_integral_v<T>) {
		T ret = a + b;
		if (ret >= MOD) ret -= MOD;
		return ret;
	}
	else return a + b;
}

template <typename T>
inline T Sub(T a, T b) {
	if constexpr (is_integral_v<T>) {
		T res = a - b;
		if (res < T(0)) res += MOD;
		return res;
	}
	else return a - b;
}

template <typename T>
inline T Mul(T a, T b) {
	if constexpr (is_integral_v<T>) {
		return T((1ll * a * b) % MOD);
	}
	else return a * b;
}

template <typename T>
inline T Div(T a, T b) {
	if constexpr (is_integral_v<T>) {
		return Mul(a, ipow(b, MOD-2));
	}
	else return a / b;
}


// returns {rref, rank, det, inv}
template <typename T, bool do_inv = false>
tuple<vector<vector<T>>, int, T, vector<vector<T>>> Gaussian_Elimination(vector<vector<T>> a) {
	int n = a.size(), m = a[0].size(), rank = 0;

	vector<vector<T>> out;
	T det = T(1);

	if constexpr (do_inv){
		out.resize(n, vector<T>(m, T(0)));
		for (int i = 0; i < n; i++) out[i][i] = T(1);
	}
	
	// set a[*][i], expect for one a[j][i]
	for (int i = 0; i < m; i++) {
		if (rank == n) break;
		if (IsZero(a[rank][i])) {
			int idx = -1;

			// If T is floating-point type, use largest abs to handle precision.
			if constexpr (is_floating_point_v<T>){
				T mx = T(0);
				for (int j = rank + 1; j < n; j++) {
					T abs_val = std::abs(a[j][i]);
					if (abs_val > mx) {
						mx = abs_val;
						idx = j;
					}
				}
			}
			else {
				for (int j = rank + 1; j < n; j++) {
					if (!IsZero(a[j][i])) {
						idx = j;
						break;
					}
				}
			}
			if (idx == -1 || IsZero(a[idx][i])) {
				det = T(0);
				continue;
			}
			for (int k = 0; k < m; k++) {
				a[rank][k] = Add(a[rank][k], a[idx][k]);
				if constexpr (do_inv) out[rank][k] = Add(out[rank][k], out[idx][k]);
			}
		}
		det = Mul(det, a[rank][i]);
		T coeff = Div(T(1), a[rank][i]);
		for (int j = 0; j < m; j++) a[rank][j] = Mul(a[rank][j], coeff);
		if constexpr (do_inv) {
			for (int j = 0; j < m; j++) out[rank][j] = Mul(out[rank][j], coeff);
		}
		for (int j = 0; j < n; j++) {
			if (rank == j) continue;
			T t = a[j][i];
			for (int k = 0; k < m; k++) a[j][k] = Sub(a[j][k], Mul(a[rank][k], t));
			if constexpr (do_inv) {
				for (int k = 0; k < m; k++) out[j][k] = Sub(out[j][k], Mul(out[rank][k], t));
			}
		}
		rank++;
	}
	return {a, rank, det, out};
}

// returns {R, c, {basis[0], basis[1], ..., basis[R-1]}}
// If linear system has no answer, R = -1
template <typename T>
tuple<int, vector<T>, vector<vector<T>>> solve_linear_system(vector<vector<T>> A, vector<T> b) {
	int n = A.size();
	int m = A[0].size();
	vector<vector<T>> M(n, vector<T>(m + 1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			M[i][j] = A[i][j];
		}
		M[i][m] = b[i];
	}

	auto [rref, rank, det, out] = Gaussian_Elimination<T, false>(M);

	for (int i = 0; i < n; ++i) {
		if (IsZero(rref[i][m])) continue;
		bool all_zero = true;
		for (int j = 0; j < m; ++j) {
			if (!IsZero(rref[i][j])) {
				all_zero = false;
				break;
			}
		}
		if (all_zero) return { -1, {}, {} };
	}

	vector<int> cols;
	for (int i = 0; i < n; i++) {
		int piv_col = 0;
		while (piv_col < m && IsZero(rref[i][piv_col])) piv_col++;
		if (piv_col == m) break;
		cols.push_back(piv_col);
	}

	// Compute particular solution
	vector<T> sol(m, T(0));
	for (int i = 0; i < SZ(cols); i++) sol[cols[i]] = Div(rref[i][m], rref[i][cols[i]]);

	// Compute basis
	vector<vector<T>> basis;
	for (int i = 0; i < m; i++) {
		if (binary_search(all(cols), i)) continue;

		vector<T> bs(m, T(0));
		bs[i] = T(1);
		for(int j = 0; j < SZ(cols); j++) bs[cols[j]] = Sub(T(0), Div(rref[j][i], rref[j][cols[j]]));
		basis.push_back(bs);
	}

	return {SZ(basis), sol, basis};
}

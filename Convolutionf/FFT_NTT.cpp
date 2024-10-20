/**
 * Original Source: https://github.com/kth-competitive-programming/kactl/tree/main/content/numerical
 * I changed it to match my coding style.
 * 
 * 
 * fft(a):
 * 입력 벡터 a의 size N은 2^m 꼴이여야 합니다.
 * 다항식 g(x) = a[0] + a[1]x + a[2]x^2 + ... + a[N-1]x^(N-1)에 대해,
 * fft(a)는 벡터 a를 (g(1), g(w), g(w^2), ..., g(w^(N-1)))로 변환합니다.
 * w = e^(2*pi*i/N)
 * 
 * 
 * ntt(a):
 * 입력 벡터 a의 size N은 2^m <= 2^b 꼴이여야 합니다. (MOD = a*2^b+1, root=MOD의 원시근)
 * 다항식 g(x) = a[0] + a[1]x + a[2]x^2 + ... + a[N-1]x^(N-1)에 대해,
 * ntt(a)는 벡터 a를 (g(1), g(w), g(w^2), ..., g(w^(N-1)))를 MOD로 나눈 나머지로 변환합니다.
 * w = root^((MOD-1)/N)
 * 
 * conv(a, b): 다항식 a*b 계산 후 반환
 * convMod(a, b): 다항식을 Mod로 나눈 나머지 반환, 정확도 높은 구현
 * conv_ntt(a, b): 다항식을 Mod로 나눈 나머지 반환, NTT를 활용해 구현
 * 
 * FFT 계산을 위해 잘 알려진 opt-trick들을 활용합니다.
 * FFT 2번으로 conv 계산, 2-in-1 trick(Reference: https://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf)
 * 정확도를 위해 sqrt(Mod)로 다항식 분리(Reference: https://algoshitpo.github.io/2020/05/20/fft-ntt/)
 */

typedef complex<double> C;
typedef vector<double> vd;
typedef vector<ll> vl;

void fft(vector<C>& a) {
	int n = SZ(a),L = 31 - __builtin_clz(n);

	// 미리 w^k 계산
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);
	for (static int k=2;k<n;k*=2){
		R.resize(n); rt.resize(n);

		auto x = polar(1.0L, acos(-1.0L) / k);
		for(int i=k;i<2*k;i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	// 반전 비트 수열 계산 후 재배열
	vector<int> rev(n);
	for(int i=0;i<n;i++) rev[i] = (rev[i/2] | (i&1) << L) / 2;
	for(int i=0;i<n;i++) if (i<rev[i]) swap(a[i], a[rev[i]]);

	// 쿨리-튜키
	for (int k=1;k<n;k*=2)
		for (int i=0;i<n;i+=2*k) for(int j=0;j<k;j++) {
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
			a[i+j+k] = a[i+j]-z;
			a[i+j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(SZ(a)+SZ(b)-1);
	int L = 32 - __builtin_clz(SZ(res)), n = 1 << L;

	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	for(int i=0;i<SZ(b);i++) in[i].imag(b[i]);

	fft(in);
	for (C& x : in) x *= x;
	for(int i=0;i<n;i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);

	for(int i=0;i<SZ(res);i++) res[i] = imag(out[i]) / (4*n);
	return res;
}

const ll mod_ntt = (119 << 23) + 1, root = 62; // = 998244353

void ntt(vl &a) {
	int n = SZ(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k=2,s=2; k<n; k*=2,s++) {
		rt.resize(n);
		ll z[] = {1, ipowM(root, mod_ntt >> s, mod_ntt)};
		for(int i=k;i<2*k;i++) rt[i] = rt[i/2] * z[i&1] % mod_ntt;
	}
	vector<int> rev(n);
	for(int i=0;i<n;i++) rev[i] = (rev[i/2] | (i&1) << L) / 2;
	for(int i=0;i<n;i++) if (i<rev[i]) swap(a[i], a[rev[i]]);
	for (int k=1;k<n;k*=2)
		for (int i=0;i<n;i+=2*k) for(int j=0;j<k;j++) {
			ll z = rt[j+k] * a[i+j+k] % mod_ntt, &ai = a[i+j];
			a[i+j+k] = ai - z + (z > ai ? mod_ntt : 0);
			ai += (ai + z>= mod_ntt ? z - mod_ntt : z);
		}
}

vl conv_ntt(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = SZ(a)+SZ(b)-1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = ipowM(n, mod_ntt - 2, mod_ntt);

	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);

	for(int i=0;i<n;i++) out[-i & (n - 1)] = (ll)L[i]*R[i]%mod_ntt*inv%mod_ntt;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(SZ(a)+SZ(b)-1);
	int B=32-__builtin_clz(SZ(res)), n=1<<B, cut=int(sqrt(M));

	vector<C> L(n), R(n), outs(n), outl(n);
	for(int i=0;i<SZ(a);i++) L[i] = C((int)a[i]/cut, (int)a[i]%cut);
	for(int i=0;i<SZ(b);i++) R[i] = C((int)b[i]/cut, (int)b[i]%cut);
	fft(L), fft(R);

	for(int i=0;i<n;i++) {
		int j = -i & (n - 1);
		outl[j] = (L[i]+conj(L[j])) * R[i] / (2.0*n);
		outs[j] = (L[i]-conj(L[j])) * R[i] / (2.0*n) / 1i;
	}
	fft(outl), fft(outs);

	for(int i=0;i<SZ(res);i++) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5)+ll(real(outs[i])+.5);
		res[i] = ((av%M*cut + bv)%M*cut + cv)%M;
	}
	return res;
}

/**
 * Suffix Array & LCP Array
 * First element of sa is SZ(S)
 * isa is inverse of sa (isa[sa[i]]=i)
 * lcp stores longest common prefix between sa[i], sa[i+1]
 * O(NlogN)
 * 
 *  **CONSIDER DELETING _chk IF WRONG ANSWER**
 * 
 * Original Code: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/strings%20(14)/Light/SuffixArray%20(14.4).h
 * Changed it to fit my coding style
 */

struct SuffixArray {
	string S;
	int N;
	vector<int> sa, isa, lcp;
	void init(string _S) { N = SZ(S = _S)+1; genSa(); genLcp(); }

	void genSa() { // sa has size sz(S)+1, starts with sz(S)
		sa = isa = vector<int>(N);
		sa[0] = N-1;
		iota(1+all(sa),0);
		sort(1+all(sa),[&](int a, int b) { return S[a] < S[b]; });
		for(int i=1;i<N;++i) {
			int a = sa[i-1], b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; 
		}
		for (int len = 1; len < N; len *= 2) { // currently sorted
			// by first len chars
			vector<int> s(sa), is(isa), pos(N); iota(all(pos),0);
			for(auto &t: s) {
				int T=t-len;
				if (T>=0) sa[pos[isa[T]]++] = T;
			}
			int _chk=0;
			for(int i=1;i<N;++i) {
				int a = sa[i-1], b = sa[i]; /// verify that nothing goes out of bounds
				isa[b] = is[a]==is[b]&&is[a+len]==is[b+len]?isa[a]:i;
				if(isa[b]!=i)_chk=1;
			}
			if(_chk==0)break;
		}
	}
	void genLcp() { // Kasai's Algo
		lcp = vector<int>(N-1);
		int h = 0;
		for(int b=0;b<N-1;++b) {
			int a = sa[isa[b]-1];
			while (a+h < SZ(S) && S[a+h] == S[b+h]) ++h;
			lcp[isa[b]-1] = h;
			if (h) h--;
		}
		/// if we cut off first chars of two strings
		/// with lcp h then remaining portions still have lcp h-1

		// lcp로 RMQ 만들기
		// R.init(lcp);
	}
	/*
	RMQ<int> R; 
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
		if (a == b) return sz(S)-a;
		int l = isa[a], r = isa[b]; if (l > r) swap(l,r);
		return R.query(l,r-1);
	}
	*/
};
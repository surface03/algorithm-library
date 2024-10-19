/**
 * Line Container
 * Container where you can add lines of the form kx + m, and query maximum/minimum values at points x.
 * 
 * add(k, m): Add line kx + m
 * query(x): Line L where max(f(x)) == L(x) (min(f(x)) == L(x) when is_max == false)
 * _upd(x, y): update x->p to intersection of *x, *y
 * 
 * Original Code: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
 * Modified to fit my code style.
 */

template<typename T = long long, bool is_max = true>
struct LineContainer {

	static constexpr T inf = numeric_limits<T>::has_infinity?numeric_limits<T>::infinity():numeric_limits<T>::max();

	struct Line {
		mutable T k, m, p;

		bool operator<(const Line& o) const {return is_max ? k < o.k : k > o.k;}
		bool operator<(T x) const { return p < x; }
		T operator()(T x) const { return k * x + m; }
	};

	multiset<Line, less<>> hull;

	LineContainer() = default;

	inline T div(T a, T b) {
		if constexpr (is_integral<T>::value) return a/b - ((a^b)<0 && a%b);
		else return a/b;
	}

	bool _upd(multiset<Line>::iterator x, multiset<Line>::iterator y) {
		if (y == hull.end()) return x->p = inf, false;
		if (x->k == y->k) x->p = ((is_max ? x->m > y->m : x->m < y->m) ? inf : -inf);
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}

	void add(T k, T m) {
		auto z = hull.insert({k, m, 0}), y = z++, x = y;
		while (_upd(y, z)) z = hull.erase(z);
		if (x != hull.begin() && _upd(--x, y)) _upd(x, y = hull.erase(y));
		while ((y = x) != hull.begin() && (--x)->p >= y->p) _upd(x, hull.erase(y));
	}

	Line query(T x) {
		assert(!hull.empty());
		auto l = hull.lower_bound(x);
		return *l;
	}
};

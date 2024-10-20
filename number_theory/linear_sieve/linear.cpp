/**
 * Linear Sieve
 * 
 * This template can perform the following two tasks
 * 
 * Calculate is_prime(1), is_prime(2), ..., is_prime(MAXN)
 * For multiplicative function f, calculate f(1), f(2), ..., f(MAXN)
 * 
 * 
 * Example is the Euler's totient function calculation
 * 
 * O(MAXN)
 */

const int MAXN = 40000000;
vector<int> prime;
bool not_prime[MAXN + 10];
ll phi[MAXN + 10];

void linear_sieve() {
	phi[1] = 1;
	for (int i = 2; i <= MAXN; ++i) {
		if (!not_prime[i]) {
			prime.push_back(i);

			// i가 소수일 때 값 대입
			phi[i] = i - 1;
		}
		for (int j = 0; j < (int)prime.size() && 1ll*i * prime[j] <= 1ll*MAXN; ++j) {
			not_prime[i * prime[j]] = true;

			if (i % prime[j] == 0) {
				// i가 prime[j]의 배수인 경우 대입
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				// i가 prime[j]의 배수가 아닌 경우 대입
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
	}
}
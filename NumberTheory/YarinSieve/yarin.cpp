/**
 * Super fast & Memory-tight Sieve by Yarin
 * 
 * Original Code: https://github.com/mejibyte/competitive_programming/blob/master/lib/Documentation/9thinksYouNeed-ACMSolver/sieve%20by%20yarin.cpp
 */

// All prime numbers up to this
constexpr int MAXSIEVE = 1000077376;
constexpr int MAXSIEVEHALF = 500038688;

// sqrt(MAXSIEVE)/2
constexpr int MAXSQRT = 15812;

char a[MAXSIEVE/16+2]; 

//have to check for even numbers
void yarin_sieve() {
	int i,j; 
	memset(a,255,sizeof(a)); 
	a[0]=0xFE; 
	for(i=1;i<MAXSQRT;i++) 
		if (a[i>>3]&(1<<(i&7))) 
			for(j=i+i+i+1;j<MAXSIEVEHALF;j+=i+i+1) 
				a[j>>3]&=~(1<<(j&7));
}

inline bool is_prime_yarin(int n){ return (n%2)?(a[n>>4]&(1<<((n>>1)&7))):(n==2); }
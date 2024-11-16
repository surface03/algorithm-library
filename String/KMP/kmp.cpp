/**
 * Knuth–morris–pratt
 * 
 * get_fail(S): 
 * S의 실패함수를 구한다.
 * fail[i]: S[0..i]중 일치하는 최대 접두사-접미사 길이 (자기 자신 제외)
 * 
 * KMP(A, B):
 * A[i..i+SZ(B)-1] == B인 i 모두 반환
 */

vector<int> get_fail(string &B){
	vector<int> ret;
	int M=B.size();
	ret.resize(M, 0);
	for(int i=1,j=0;i<M;i++){
		while(j>0 && B[i]!=B[j])j=ret[j-1];
		if(B[i]==B[j])ret[i]=++j;
	}
	return ret;
}
vector<int> KMP(string &A, string &B){
	vector<int> ret;
	auto fail=get_fail(B);
	int N=A.size();
	int M=B.size();
	for(int i=0,j=0;i<N;i++){
		while(j>0 && A[i]!=B[j])j=fail[j-1];
		if(A[i]==B[j]){
			if(j==M-1){
				ret.push_back(i-j);
				j=fail[j];
			}
			else j++;
		}

	}
	return ret;
}
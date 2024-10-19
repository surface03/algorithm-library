const int B=330;

// 구간 [s, e]를 제곱근 분할법으로 처리
for(int i=s;i<=e;){
	if(i%B==0 && i+B<e){ // i%B==0 && i+B-1<=e
		// bkt[i/B] 사용
		i+=B;
	}
	else{
		// arr[i] 사용
		i++;
	}
}
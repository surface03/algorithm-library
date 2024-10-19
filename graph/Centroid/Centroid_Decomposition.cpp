// 서브트리 크기, 센트로이드 트리에서 부모, cd 과정 중 visit 배열
int sz[100010],cent_par[100010],used[100010];
int N;

// 두 함수는 연속해서 사용
int getSz(int now,int prv=-1){
	sz[now]=1;
	for(int i:v[now]){
		if(used[i] || i==prv) continue;
		sz[now]+=getSz(i,now);
	}
	return sz[now];
}

int getCent(int now,int prv,int sub_sz){
	for(int i:v[now]){
		if(used[i] || i==prv) continue;
		if(sz[i] > sub_sz/2) return getCent(i,now,sub_sz);
	}
	return now;
}

// 센트로이드 트리 구성
void centroid_decomposition(int now,int prv=-1){
	int cnt=getSz(now, prv);
	int cur_cent=getCent(now,prv, cnt);
	cent_par[cur_cent]=prv;
	used[cur_cent]=1;
	for(int i:v[cur_cent]){
		if(used[i]) continue;
		centroid_decomposition(i,cur_cent);
	}
}
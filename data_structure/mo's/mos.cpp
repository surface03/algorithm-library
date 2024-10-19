/**
 * Mo's Algorithm on Array
 * 
 * Modify add(), del()
 * Modify add() to {addL(), addR()}, del() to {delL(), delR()} if necessary
 * 
 * O((N+Q)sqrt(N))
 */

const int iB=330;

int a[100010],n,ans[100010],cur_ans;

struct Query{
	int frq,req,qnum;
	bool operator<(const Query&r)const{
		if(req/iB==r.req/iB)return frq<r.frq;
		return req<r.req;
	}
} Q[100010];

// a[x]를 추가/삭제하는 함수
// 예시는 서로 다른 원소 개수 관리
int cnt[1000010];
void add(int x){
	if(cnt[a[x]]==0)cur_ans++;
	cnt[a[x]]++;
}
void del(int x){
	cnt[a[x]]--;
	if(cnt[a[x]]==0)cur_ans--;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	int M;
	scanf("%d",&M);
	for(int i=0; i<M; i++){
		scanf("%d %d",&Q[i].frq, &Q[i].req);
		Q[i].qnum = i;
	}
	sort(Q, Q+M);
	int fr=1, re=0;
	for(int i=0; i<M; i++){
		while(fr>Q[i].frq) add(--fr);
		while(re<Q[i].req) add(++re);
		while(re>Q[i].req) del(re--);
		while(fr<Q[i].frq) del(fr++);
		ans[Q[i].qnum] = cur_ans;
	}
	for(int i=0; i<M; i++) printf("%d\n", ans[i]);
}

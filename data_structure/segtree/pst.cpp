#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int M = 524288;

struct node{
	int val;
	node *l,*r;
	node() : val(0), l(NULL), r(NULL) {}
};

node* tree[530000];
int a[500010],N;

void init(node* now,int s,int e){
	if(s==e){
		now->val=0;
		return;
	}
	int m=(s+e)/2;
	now->l=new node();
	now->r=new node();
	init(now->l,s,m);
	init(now->r,m+1,e);
	now->val=0;
}

void upd(node* pre, node* now, int s,int e,int idx){
	if(s==e){
		now->val=pre->val + 1;
		return;
	}
	int m=(s+e)/2;
	if(idx<=m){
		now->l=new node();
		now->r=pre->r;
		upd(pre->l,now->l,s,m,idx);
	}
	else{
		now->l=pre->l;
		now->r = new node();
		upd(pre->r,now->r,m+1,e,idx);
	}
	now->val = now->l->val + now->r->val;
}

// 구간에서 k번째 원소 반환
int kth(node *i,node *j,int s,int e,int k){
	if(s==e){
		return s;
	}
	int m=(s+e)/2;
	if(j->l->val - i->l->val >= k)return kth(i->l,j->l,s,m,k);
	else return kth(i->r,j->r,m+1,e,k-(j->l->val - i->l->val));
}

// 구간에서 k 이하 원소 개수 반환
int Query(node *i,node *j,int s,int e,int k){
	if(s>k)return 0;
	if(e<=k)return j->val - i->val;
	int m=(s+e)/2;
	return Query(i->l,j->l,s,m,k) + Query(i->r,j->r,m+1,e,k);
}

// 수열과 쿼리
// 1 x: 배열 끝에 x 추가
// 2 L R x: A[L...R] 중 x 이하 원소 개수
// 3 L R x: A[L...R] 중 x번째로 작은 원소
int main(){
	tree[0]=new node();
	init(tree[0],0,M-1);
	int Q;
	scanf("%d",&Q);
	while(Q--){
		int op,L,R,x;
		scanf("%d",&op);
		if(op==1){
			N++;
			scanf("%d",&x);
			tree[N]=new node();
			upd(tree[N-1],tree[N],0,M-1,x);
		}
		if(op==2){
			scanf("%d %d %d",&L,&R,&x);
			printf("%d\n", Query(tree[L-1],tree[R],0,M-1,x));
		}
		if(op==3){
			scanf("%d %d %d",&L,&R,&x);
			printf("%d\n", kth(tree[L-1],tree[R],0,M-1,x));
		}
	}
}
/**
 * Persistent Segment Tree(1-based)
 * 
 * 배열 끝에 원소 삽입
 * 구간에서 k 이하 원소 개수
 * 구간에서 k번째 원소 개수(1-based)
 * 
 * append, kth, count: O(logN)
 */

const int MAXN = 500050;

struct PersistentSegTree{
	// [0, M-1] 범위의 수 관리
	// 필요에 따라 좌표압축
	const int M = 524288;

	struct node{
		int val;
		node *l,*r;
		node() : val(0), l(NULL), r(NULL) {}
		~node() {
			if (l) delete l;
			if (r) delete r;
		}
	};

	node* tree[MAXN];
	int N;

	PersistentSegTree(){
		N=0;
		memset(tree,0,sizeof tree);
		tree[0]=new node();
		init(tree[0],0,M-1);
	}

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

	int kth(node *i,node *j,int s,int e,int k){
		if(s==e){
			return s;
		}
		int m=(s+e)/2;
		if(j->l->val - i->l->val >= k)return kth(i->l,j->l,s,m,k);
		else return kth(i->r,j->r,m+1,e,k-(j->l->val - i->l->val));
	}

	int count(node *i,node *j,int s,int e,int k){
		if(s>k)return 0;
		if(e<=k)return j->val - i->val;
		int m=(s+e)/2;
		return count(i->l,j->l,s,m,k) + count(i->r,j->r,m+1,e,k);
	}

	// A[N+1] <- x 대입
	void append(int x){
		N++;
		tree[N]=new node();
		upd(tree[N-1],tree[N],0,M-1,x);
	}

	// A[L...R]에서 k번째 원소 반환
	int kth(int L,int R,int k){
		return kth(tree[L-1],tree[R],0,M-1,k);
	}

	// A[L...R]에서 k 이하 원소 개수 반환
	int count(int L,int R,int k){
		return count(tree[L-1],tree[R],0,M-1,k);
	}
};

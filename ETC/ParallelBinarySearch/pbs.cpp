struct Info{
	int fr,re,mid,ans;
	Info(){
		fr=re=mid=0;
		ans=-1;
	}
}info[MAXN];

vector<int> qs[M];

void process(){
	for(int i=1;i<=Q;i++){
		// info[i].fr=1;
		// info[i].re=M;
	}

	vector<int> mid[M+10];

	while(1){
		for(int i=0;i<M+10;i++)mid[i].clear();

		bool lef=false;
		for(int i=1;i<=Q;i++){
			if(info[i].fr>info[i].re)continue;
			lef=true;
			mid[(info[i].fr+info[i].re)/2].pb(i);
		}
		if(!lef)break;
	}
	for(int i=1;i<=Q;i++){
		if(info[i].ans==-1)cout<<"No\n";
		else cout<<info[i].ans<<"\n";
	}
}
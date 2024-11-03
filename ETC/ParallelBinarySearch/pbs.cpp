struct Info{
	int fr,re,mid,ans;
	Info(){
		fr=re=mid=0;
		ans=-1;
	}
}info[300010];

vector<int> qs[MAXN]

void process(){
	for(int i=1;i<=Q;i++){
		// info[i].fr=1;
		// info[i].re=M;
	}

	while(1){
		bool lef=false;
		for(int i=1;i<=N;i++){
			if(info[i].fr>info[i].re)continue;
			lef=true;
			qs[(info[i].fr+info[i].re)/2].pb(i);
		}
		if(!lef)break;
	}
	for(int i=1;i<=Q;i++){
		if(info[i].ans==-1)cout<<"No\n";
		else cout<<info[i].ans<<"\n";
	}
}
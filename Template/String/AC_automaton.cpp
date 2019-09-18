struct Trie
{
	static const int N=101010,M=26;
	int ne[N][M],fail[N],fa[N],L,rt,cnt[N];
	void init()
	{
		fail[0]=N-1;
		for (int i=0;i<M;++i)
			ne[N-1][i]=0;
		memset(cnt,0,sizeof(cnt));
		L=0;
		rt=newnode();
	}
	int newnode()
	{
		for (int i=0;i<M;++i)
			ne[L][i]=0;
		return L++;
	}
	void add(char* s)
	{
		int p=rt;
		for (int i=0;s[i];++i)
		{
			int c=s[i]-'a';
			if (!ne[p][c])
			{
				ne[p][c]=newnode();
				fa[L-1]=p;
			}
			p=ne[p][c];
		}
		cnt[p]++;
	}
	void build()
	{
		V v;
		v.pb(rt);
		for (int i=0;i<v.size();++i)
		{
			int c=v[i];
			for (int j=0;j<M;++j)
			{
				if (ne[c][j])
				{
					v.pb(ne[c][j]);
					fail[ne[c][j]]=ne[fail[c]][j];
				}
				else
					ne[c][j]=ne[fail[c]][j];
			}
		}
	}
	void ac_auto(char* s)
	{
		int p=rt;
		for (int i=0;s[i];++i)
		{
			int c=s[i]-'a';
			while (!ne[p][c]&&p)
				p=fail[p];
			int tmp=p=ne[p][c];
			while (tmp)
			{
				if (cnt[tmp]!=-1)//if macth,do... 
				{
					
					cnt[tmp]=-1;
				} 
				tmp=fail[tmp];
			}
		}
	}
}trie;
/*
	poj 2778 DNA Sequence
	AC 自动机跑出邻接矩阵
	矩阵快速幂求方案数 
*/
int rt,id,hs[maxn],ne[maxn][10],vis[maxn],fail[maxn];
inline int newnode(){
	++id;
	for (int i=0;i<4;++i)
		ne[id][i]=0;
	return id;
}
void init(){
	hs['A']=0;
	hs['C']=1;
	hs['T']=2;
	hs['G']=3;
	id=-1;
	fail[0]=maxn-1;
	for (int i=0;i<4;++i)
		ne[maxn-1][i]=0;
	memset(vis,0,sizeof(vis));
	rt=newnode();
}
void ins(char* s){
	int p=rt;
	for (int i=0;s[i];++i){
		int c=hs[s[i]];
		if (!ne[p][c])
			ne[p][c]=newnode();
		p=ne[p][c];
	}
	vis[p]=1;
}
void build(){
	vector<int> v;
	v.pb(rt);
	for (int i=0;i<sz(v);++i){
		int c=v[i];
		for (int j=0;j<4;++j){
			if (ne[c][j]){
				v.pb(ne[c][j]);
				fail[ne[c][j]]=ne[fail[c]][j];
			}
			else
				ne[c][j]=ne[fail[c]][j];
			vis[ne[c][j]]|=vis[ne[fail[c]][j]];// 凡是 fail指针 指向死态的点, 本身也是死态 ！！ 
		}
	}
}
char s[maxn];
int main()
{
	int n,m;
	while (scanf("%d%d",&m,&n)!=EOF){
		init();
		for (int i=1;i<=m;++i){
			scanf("%s",s);
			ins(s);
		}
		build();
		matrix T(id+1,id+1,0);
		for (int i=0;i<=id;++i){
			if (vis[i])
				continue;
			for (int j=0;j<4;++j)
				if (!vis[ne[i][j]])
					T.a[i][ne[i][j]]++;
		}
		matrix res=T^n;
		ll ans=0;
		for (int i=0;i<=id;++i)
			ans=(ans+res.a[0][i])%mod;
		cout<<ans<<"\n";
	}
	return 0;
} 

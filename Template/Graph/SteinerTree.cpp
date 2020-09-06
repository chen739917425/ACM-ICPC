vector<P> e[maxn];
bool vis[maxn];
queue<int> q;
int f[maxn][1<<15];
void spfa(int s){
	while(sz(q)){
		int u = q.front();
		q.pop();
		vis[u]=0;
		for (auto i:e[u]){
			int v=i.fi,w=i.se;
			if(f[v][s]>f[u][s]+w){
				f[v][s]=f[u][s]+w;
				if(!vis[v])
					q.push(v),vis[v]=1;
			}
		}
	}
}
int SteinerTree(int* a,int m,int n){
	for (int i=1;i<=n;++i)
		for (int j=0;j<(1<<m);++j)
			f[i][j]=INF;
	for (int i=1;i<=m;++i)
		f[a[i]][1<<(i-1)]=0;
	for (int s=1;s<(1<<m);++s){
		for (int i=1;i<=n;++i){
			for(int j=(s-1)&s;j;j=(j-1)&s){
				if(f[i][j]+f[i][s^j]<f[i][s])
					f[i][s]=f[i][j]+f[i][s^j];
			}
			if(f[i][s]<INF)	q.push(i),vis[i]=1;
		}
		spfa(s);
	}
	int ans=INF;
	for (int i=1;i<=n;++i)	
		ans=min(ans,f[i][(1<<m)-1]);
	return ans;
}

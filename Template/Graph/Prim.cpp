int e[N][N],d[N];
int vis[N];
ll Prim(int n){
	memset(vis,0,sizeof(vis));
	memset(d,0x3f,sizeof(d));
	ll ans=0;
	int u=1;
	vis[u]=1;
	d[u]=0;
	for (int i=1;i<n;++i){
		int v=0;
		for (int j=1;j<=n;++j){
			if (vis[j])
				continue;
			d[j]=min(d[j],e[u][j]);
			if (d[v]>d[j])
				v=j;
		}
		if (!v)
			return -1;
		vis[v]=1;
		ans+=d[v];
		u=v;
	}
	return ans;
}

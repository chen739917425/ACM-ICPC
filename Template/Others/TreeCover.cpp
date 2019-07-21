/*
	O(nk) get the minimun of vertex with k radius could cover whole tree
*/
int TreeCover(int n,int k){
	for (int i=1;i<=n;++i)
		a[i]=i;
	memset(dis,INF,sizeof(dis));
	sort(a+1,a+1+n,[&](int x,int y){return dep[x]>dep[y];});
	int cnt=0;
	for (int i=1;i<=n;++i){
		int u=a[i];
		for (int j=1,f=fa[u];j<=k;++j,f=fa[f])
			dis[u]=min(dis[u],dis[f]+j);
		if (dis[u]>k){
			for (int j=0;j<k;++j)
				u=fa[u];
			dis[u]=0;
			cnt++;
			for (int j=1,f=fa[u];j<=k;++j,f=fa[f])
				dis[f]=min(dis[f],j);
		}
	}
	return cnt;
}

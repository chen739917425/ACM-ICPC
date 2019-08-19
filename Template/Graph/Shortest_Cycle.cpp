int dis[maxn][maxn],w[maxn][maxn]; // w[i][j]为(i,j)的边权 
int shortest_cycle(int n){
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			dis[i][j]=w[i][j];
	int ans=INF; // 3 * INF < INT_MAX 
	for (int k=1;k<=n;++k){
		for (int i=1;i<k;++i)
			for (int j=i+1;j<k;++j)
				ans=min(ans,w[k][i]+w[k][j]+dis[i][j]); 
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	return ans==INF?-1:ans;
}

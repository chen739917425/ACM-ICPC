int link[maxn];
bool vis[maxn];
V G[maxn];
void init(int m)
{
	Clear(link,-1);
	for (int i=0;i<=m;++i)
		G[i].clear();
}
bool find(int u)
{
	int sz=G[u].size();
	for (int i=0;i<sz;++i)
	{
		int v=G[u][i];
		if (!vis[v])
		{
			vis[v]=1;
			if (link[v]==-1||find(link[v]))
			{
				link[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int match(int n)
{
	int cnt=0;
	for (int i=1;i<=n;++i)
	{	
		memset(vis,0,sizeof(vis));
		if (find(i))
			cnt++;
	}
	return cnt;
}

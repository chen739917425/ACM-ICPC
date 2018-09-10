struct Edge 
{
	int v,d,ne;
};
Edge edge[maxn*5];
int d[maxn],vis[maxn],head[maxn],cnt;
void add(int u,int v,int d)
{
	edge[++cnt].ne=head[u];
	edge[cnt].v=v;
	edge[cnt].d=d;
	head[u]=cnt;
}
void dij(int s,int n)
{
	for (int i=0;i<=n;++i)
		d[i]=INF;
	d[s]=0;
	SQ q;
	q.push(mp(0,s));
	while (!q.empty())
	{
		P p=q.top();
		q.pop();
		int u=p.se;
		if (vis[u])
			continue;
		vis[u]=1;
		for (int i=head[u];i;i=edge[i].ne)
		{
			int v=edge[i].v,dis=edge[i].d;
			if (d[u]+dis<d[v])
			{
				d[v]=d[u]+dis;
				q.push(mp(d[v],v));
			}
		}
	}
}

struct Edge
{
	int v,d,ne;
}edge[maxn];
bool in[maxn];
int cnt=0,vis[maxn],head[maxn];
void add(int u,int v,int w)
{
	edge[++cnt].ne=head[u];
	edge[cnt].v=v;
	edge[cnt].d=w;
	head[u]=cnt;
}
bool spfa(int s,int n,double value)
{
	Q q;
	d[s]=0;
	in[s]=1;
	q.push(s);
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		in[u]=0;
		for (int i=head[u];i;i=edge[i].ne)
		{
			int v=edge[i].v,dis=edge[i].d;
			if (dis+d[u]<d[v])
			{
				d[v]=dis+d[u];
				if (!in[v])
				{
					if (++vis[v]>n)
						return 0;
					q.push(v);
					in[v]=1;
				}
			}
		}
	}
	return 1;
}

struct edge{
	int ne,v,w;
}e[maxn<<1];
int head[maxn],cnt=1;
void add(int u,int v,int w){
	e[++cnt].ne=head[u];
	e[cnt].v=v;e[cnt].w=w;
	head[u]=cnt;
	e[++cnt].ne=head[v];
	e[cnt].v=u;e[cnt].w=0;
	head[v]=cnt;
}
int d[maxn];
queue<int> q;
bool bfs(int s,int t){
	memset(d,0,sizeof(d));
	while (sz(q)) q.pop();
	q.push(s);d[s]=1;
	while (sz(q)){
		int u=q.front();q.pop();
		for (int i=head[u];i;i=e[i].ne){
			int v=e[i].v,w=e[i].w;
			if (w&&!d[v]){
				q.push(v);
				d[v]=d[u]+1;
				if (v==t) return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int t,int flow){
	if (u==t)
		return flow;
	int rest=flow,k;
	for (int i=head[u];i;i=e[i].ne){
		int v=e[i].v;
		if (e[i].w&&d[v]==d[u]+1){
			k=dfs(v,t,min(rest,e[i].w));
			if (!k) d[v]=0;
			e[i].w-=k;
			e[i^1].w+=k;
			rest-=k;
		}
	}
	return flow-rest;
}
int dinic(int s,int t){
	int flow=0,mxf=0;
	while (bfs(s,t))
		while (flow=dfs(s,t,INF))
			mxf+=flow;
	return mxf;
}

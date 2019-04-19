// 有向图强连通分量 
int dfn[maxn],low[maxn],sign[maxn],num,tim;
bool ins[maxn];
stack<int> s;
vector<int> G[maxn];
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	s.push(u);
	ins[u]=1;
	for (int i=0;i<sz(G[u]);++i)
	{
		int v=G[u][i];
		if (!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if (ins[v])
			low[u]=min(low[u],low[v]);
	}
	if (dfn[u]==low[u])
	{
		sign[u]=++num;
		while (s.top()!=u)
		{
			sign[s.top()]=num;
			ins[s.top()]=0;
			s.pop();
		}
		s.pop();
		ins[u]=0;
	}
}
// 无向图求割与桥
int dfn[maxn],low[maxn],tim,root,rtson;
vector<int> G[maxn],cutvex;
vector<P> bridge;
void tarjan(int u,int fa)// for (i=1;i<=n;++i) if (!dfn[i]) root=i,rtson=0,tarjan(i,0); 
{
	dfn[u]=low[u]=++tim;
	bool isCut=0;
	for(int i=0;i<sz(G[u]);++i)
	{
		int v=G[u][i];
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v])  
				bridge.pb(mp(u,v));
			if(dfn[u]<=low[v]) 
				isCut=1;
		}
		else if(fa!=v)
			low[u]=min(low[u],dfn[v]);
	}
	if(fa==root&&rtson!=-1) 
		rtson++;
	if(rtson>1) 
		cutvex.pb(root),rtson=-1; 
	if(u!=root&&isCut)	
		cutvex.pb(u);
} 
// 无向图点双连通分量 bcc 
struct edge
{
	int v,ne;
}e[maxn<<1];
bool vis[maxn<<1];
int head[maxn],sign[maxn],dfn[maxn],low[maxn],cnt,tim,num;
vector<int> bccv[maxn],bcce[maxn];
stack<int> s;
void init()
{
	memset(head,-1,sizeof(head));
	cnt=-1;
}
inline void push_bcc(int i)
{
	int x=e[i^1].v,y=e[i].v;
	if (sign[x]!=num)
		sign[x]=num,bccv[num].pb(x);
	if (sign[y]!=num)
		sign[y]=num,bccv[num].pb(y);
	bcce[num].pb(i);
}
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	for (int i=head[u];i!=-1;i=e[i].ne)
	{
		if (vis[i])
			continue;
		vis[i]=vis[i^1]=1;
		int v=e[i].v;	
		s.push(i);
		if (!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if (dfn[u]<=low[v])
			{
				++num;
				while (s.top()!=i)
				{
					push_bcc(s.top());
					s.pop();
				}
				push_bcc(i);
				s.pop();
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}
// 无向图边双连通分量 ebc 
int head[maxn],dfn[maxn],low[maxn],cnt,num,tim;
stack<int> s; 
vector<int> ebcv[maxn];
void tarjan(int u,int fa)
{
    dfn[u]=low[u]=++tim;
    s.push(u);
    for(int i=head[u];i;i=e[i].ne)
    {
        int v=e[i].v;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        ++num;
        while(s.top()!=u)
        {
            ebcv[num].pb(s.top());
            s.pop();
        }
        ebcv[num].pb(u);
        s.pop();
    }
}

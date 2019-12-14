/*
	有向图强连通分量scc
	for (i=1;i<=n;++i)
		if (!dfn[i]) tarjan(i);
*/
int dfn[maxn],low[maxn],col[maxn],num,tim;
bool ins[maxn];
int s[maxn],top;
vector<int> G[maxn];
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	s[++top]=u;
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
		++num;
		int t;
		do{
			t=s[top--];
			ins[t]=0,col[t]=num;
		} while (t!=u);
	}
}
/*
	无向图求桥 Bridge 和边双 e-DCC
	cnt=1;
	for (i=1;i<=n;++i) 
		if (!dfn[i]) tarjan(i,0);
	for (i=1;i<=n;++i)
		if (!col[i]) ++dcc, dfs(i);
*/
int head[maxn],cnt;
int dfn[maxn],low[maxn],tim;
bool bridge[maxn<<1];
void tarjan(int u,int edge)
{
	dfn[u]=low[u]=++tim;
	for(int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v])  
				bridge[i]=bridge[i^1]=1;
		}
		else if(i!=(edge^1))
			low[u]=min(low[u],dfn[v]);
	}
}
int col[maxn],dcc;
void dfs(int u)
{
	col[u]=dcc;
	for (int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].v;
		if (col[v]||bridge[i]) continue;
		dfs(v);
	}
}
/* 
	无向图求割点 cut 和点双 v-DCC
	for (i=1;i<=n;++i)
		if (!dfn[i]) root=i,tarjan(i);
*/
int head[maxn],cnt;
int dfn[maxn],low[maxn],tim,root,num;
bool cut[maxn];
vector<int> dcc[maxn];
int s[maxn],top;
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	s[++top]=u;
	if (u==root&&head[u]==0)
	{
		dcc[++num].pb(u);
		return;
	}
	int flag=0;
	for (int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].v;
		if (!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if (dfn[u]<=low[v])
			{
				++flag;
				if (u!=root||flag>1)
					cut[u]=1;
				++num;
				int t;
				do{
					t=s[top--];
					dcc[num].pb(t);
				} while (t!=v);
				dcc[num].pb(u);
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}
/*
	点双缩点建新图, 将每个 v-DCC 与其包含的割点连边
	对割点赋新编号, 故空间开两倍
	多组数据时, 要初始化两倍空间
*/
int new_id[maxn],sz[maxn<<1];
vector<int> E[maxn<<1];
void build(){
	int id=num;
	for (int i=1;i<=n;++i)
		if (cut[i])
			new_id[i]=++id,sz[id]=1;
	for (int i=1;i<=num;++i)
		for (auto j:dcc[i])
			if (cut[j]){
				E[new_id[j]].pb(i);
				E[i].pb(new_id[j]);
			}
			else
				sz[i]++;
}
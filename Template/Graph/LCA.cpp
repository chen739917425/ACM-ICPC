/*multiply*/
int fa[maxn][32],deep[maxn],in[maxn];
V G[maxn];
void init(int n)
{
	Clear(in,0);
	for (int i=0;i<=n;++i)
		G[i].clear();
}
void dfs(int u,int f,int d)
{
	fa[u][0]=f;
	deep[u]=d;
	for (int i=1;i<=20;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	int sz=G[u].size();
	for (int i=0;i<sz;++i)
	{
		int v=G[u][i];
		if (v!=f)
			dfs(v,u,d+1);
	}
}
int lca(int x,int y)
{
	if (deep[x]<deep[y])
		swap(x,y);
	for (int i=20,d=deep[x]-deep[y];i>=0;--i)
	{
		if (d&(1<<i))
			x=fa[x][i];
	}
	if (x==y)
		return x;
	for (int i=20;i>=0;--i)
		if (fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	return fa[x][0];
}
/*RMQ*/
int head[maxn],deep[maxn<<1],num[maxn<<1],pos[maxn<<1],ST[maxn<<1][32],cnt,tot;
struct Edge
{
	int v,ne;
}edge[maxn];
void add(int u,int v)
{
	edge[++cnt].ne=head[u];
	edge[cnt].v=v;
	head[u]=cnt;
}	
void init()
{
	tot=0;
	cnt=0;
	Clear(ans,0);
	Clear(head,0);
	Clear(pos,0);
}
void dfs(int u,int d)
{
	deep[u]=d;
	num[++tot]=u;
	if (!pos[u])
		pos[u]=tot;
	for (int i=head[u];i;i=edge[i].ne)
	{
		dfs(edge[i].v,d+1);
		num[++tot]=u;
	}
}
void ST_init(int n)
{
	for (int i=1;i<=n;++i)
		ST[i][0]=num[i];
	for (int j=1;(1<<j)<=n;++j)
		for (int i=1;i+(1<<j)-1<=n;++i)
		{
			int u=ST[i][j-1],v=ST[i+(1<<(j-1))][j-1];
			ST[i][j]=deep[u]<deep[v]?u:v;
		}
}
inline int qry(int l,int r)
{
	int k=log(double(r-l+1))/log(2.0);
	int u=ST[l][k],v=ST[r-(1<<k)+1][k];
	return deep[u]<deep[v]?u:v;
}
inline int lca(int x,int y)
{
	int l=pos[x],r=pos[y];
	if (l>r)
		swap(l,r);
	return qry(l,r);
}
/*Tarjan*/
int cnt,head[maxn],fa[maxn],ans[maxn];
bool vis[maxn];
struct qry
{
	int v,id;
	qry(int a,int b,int c):u(a),v(b),id(c){}
};
vector<qry> q[maxn];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void tarjan(int u)
{
	vis[u]=1;
	int sz=a[u].size();
	for (int i=0;i<sz;++i)
	{
		int v=q[u][i].v,id=q[u][i].id;
		if (vis[v])
			ans[id]=find(v);
	}
	for (int i=head[u];i;i=edge[i].ne)
	{
		int v=edge[i].v;
		if (vis[v])
			continue;
		tarjan(v);
		fa[v]=u;
	}
}

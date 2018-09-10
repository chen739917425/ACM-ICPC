int dfn[maxn],low[maxn],stack[maxn],sign[maxn];
bool ins[maxn];
int top,num,deep;
V G[maxn];
void tarjan(int u)
{
	dfn[u]=++deep;
	low[u]=deep;
	stack[++top]=u;
	ins[u]=1;
	int sz=G[u].size();
	for (int i=0;i<sz;++i)
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
		while (stack[top]!=u)
		{
			sign[stack[top]]=num;
			ins[stack[top--]]=0;
		}
		--top;
		ins[u]=0;
	}
}

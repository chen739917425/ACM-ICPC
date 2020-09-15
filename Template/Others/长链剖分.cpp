int dep[maxn],mxd[maxn],son[maxn],top[maxn],len[maxn],fa[maxn][30];
//查询k级祖先
void dfs1(int u,int ff){
	mxd[u]=dep[u]=dep[ff]+1;
	fa[u][0]=ff;
	for (int i=1;i<=20;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=head[u];i;i=e[i].ne){
		int v=e[i].v;
		if (v==ff)	continue;
		dfs1(v,u);
		mxd[u]=max(mxd[u],mxd[v]);
		if (mxd[v]>mxd[son[u]])	son[u]=v;
	}
}
void dfs2(int u,int ff,int t){
	top[u]=t;
	len[u]=mxd[u]-dep[t]+1;
	if (son[u])	dfs2(son[u],u,t);
	for (int i=head[u];i;i=e[i].ne){
		int v=e[i].v;
		if (v==ff||son[u]==v)	continue;
		dfs2(v,u,v);
	}
}
int hb[maxn];
vector<int> up[maxn],dw[maxn];
void init(int n){
	dfs1(1,0);
	dfs2(1,0,1);
	for (int i=1,h=0;i<=n;++i){
		if (i==top[i]){
			for (int j=0,x=fa[i][0];x&&j<len[i];++j,x=fa[x][0])
				up[i].pb(x);
			for (int j=0,x=i;j<len[i];++j,x=son[x])
				dw[i].pb(x);
		}
		h+=i==(i&-i);
		hb[i]=h-1;
	}
}
inline int qry(int u,int k){
	if (k>=dep[u])	return 0;
	if (!k)	return u;
	u=fa[u][hb[k]];
	k^=1<<hb[k];
	if (k<=dep[u]-dep[top[u]])	return dw[top[u]][dep[u]-dep[top[u]]-k];
	return up[top[u]][k-dep[u]+dep[top[u]]-1];
}
//维护子树中只与深度有关的信息
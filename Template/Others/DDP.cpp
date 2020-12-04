/*
	LuoGu P4719
	树上单点权值修改, 询问最大独立集
*/ 
int a[maxn];
vector<int> e[maxn];
int sz[maxn],son[maxn],fa[maxn];
void dfs1(int u,int ff){
	fa[u]=ff;
	for (auto v:e[u]){
		if (v==ff)	continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if (sz[v]>sz[son[u]])
			son[u]=v;
	}
}
int tim,dfn[maxn],top[maxn],bot[maxn];
void dfs2(int u,int tp){
	dfn[u]=++tim;
	top[u]=tp;
	if (son[u])	dfs2(son[u],tp),bot[u]=bot[son[u]];
	else	bot[u]=u;
	for (auto v:e[u])
		if (v!=fa[u]&&v!=son[u])
			dfs2(v,v);
}
struct Mat{
	int a[2][2];
	Mat(){}
	Mat(int _a,int _b,int _c,int _d){a[0][0]=_a,a[0][1]=_b,a[1][0]=_c,a[1][1]=_d;}
	Mat operator*(const Mat& t){
		Mat res(-inf,-inf,-inf,-inf);
		for (int i=0;i<2;++i)
			for (int j=0;j<2;++j)
				for (int k=0;k<2;++k)
					res.a[i][j]=max(res.a[i][j],a[i][k]+t.a[k][j]);
		return res;
	}
};
Mat tr[maxn<<2],g[maxn];
int f[maxn][2];
void dfs(int u){
	f[u][1]=a[u];
	for (auto v:e[u]){
		if (v==fa[u])	continue;
		dfs(v);
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
	int g0=f[u][0],g1=f[u][1];
	if (son[u])	g0-=max(f[son[u]][0],f[son[u]][1]),g1-=f[son[u]][0];
	g[dfn[u]]=Mat(g0,g0,g1,-inf);	
}
void build(int l,int r,int rt){
	if (l==r){
		tr[rt]=g[l];
		return;
	}
	int m=l+r>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	tr[rt]=tr[rt<<1]*tr[rt<<1|1];
}
Mat qry(int L,int R,int l,int r,int rt){
	if (L<=l&&r<=R)
		return tr[rt];
	int m=l+r>>1;
	Mat res(0,-inf,-inf,0);
	if (L<=m)	res=res*qry(L,R,l,m,rt<<1);
	if (R>m)	res=res*qry(L,R,m+1,r,rt<<1|1);
	return res;
}
void upd(int p,int d0,int d1,int l,int r,int rt){
	if (l==r){
		tr[rt].a[0][1]=tr[rt].a[0][0]=tr[rt].a[0][0]+d0;
		tr[rt].a[1][0]+=d1;
		return;
	}
	int m=l+r>>1;
	if (p<=m)	upd(p,d0,d1,l,m,rt<<1);
	else	upd(p,d0,d1,m+1,r,rt<<1|1);
	tr[rt]=tr[rt<<1]*tr[rt<<1|1];
}
void upd(int u,int x){
	int d0=0,d1=x-a[u];
	a[u]=x;
	while (u){
		Mat last=qry(dfn[top[u]],dfn[bot[u]],1,tim,1);
		upd(dfn[u],d0,d1,1,tim,1);
		Mat now=qry(dfn[top[u]],dfn[bot[u]],1,tim,1);
		d0=max(now.a[0][0],now.a[1][0])-max(last.a[0][0],last.a[1][0]);
		d1=now.a[0][0]-last.a[0][0];		
		u=fa[top[u]];
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=n;++i)	scanf("%d",&a[i]);
	for (int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].pb(v);
		e[v].pb(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	dfs(1);
	build(1,n,1);
	Mat ans;
	while (m--){
		int u,x;
		scanf("%d%d",&u,&x);
		upd(u,x);
		ans=qry(dfn[1],dfn[bot[1]],1,n,1);
		printf("%d\n",max(ans.a[0][0],ans.a[1][0]));
	}
	return 0;
}

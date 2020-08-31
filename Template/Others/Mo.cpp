int bs=450,bl[maxn<<1];		
int fa[maxn][25],dep[maxn],st[maxn],ed[maxn],ver[maxn<<1],tim;
int Ans,vis[maxn];
void init(){
	Ans=tim=0;
	for (int i=1;i<2*maxn;++i)
		bl[i]=i/bs+1;
}
void dfs(int u,int f){
	fa[u][0]=f;
	dep[u]=dep[f]+1;
	st[u]=++tim;ver[tim]=u;
	for (int i=1;i<=22;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for (auto v:e[u])
		if (v!=f)	dfs(v,u);
	ed[u]=++tim;ver[tim]=u;
}
inline int Lca(int x,int y){
	if (dep[x]<dep[y])	swap(x,y);
	for (int d=dep[x]-dep[y],i=0;i<=22;++i)
		if ((d>>i)&1)	x=fa[x][i];
	if (x==y)	return x;
	for (int i=22;i>=0;--i)
		if (fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
struct Q{
	int l,r,lca,id,ans;
	void init(int u,int v,int _id){
		id=_id;
		int anc=Lca(u,v);
		if (dep[u]>dep[v])	swap(u,v);
		if (anc==u)	l=st[u],r=st[v],lca=0;
		else	l=ed[u],r=st[v],lca=anc;
	}
	bool operator<(const Q& t)const{
		return bl[l]!=bl[t.l]?bl[l]<bl[t.l]:(bl[l]&1)?r<t.r:r>t.r;
	}
}qr[maxn];

inline void add(int x){

}
inline void del(int x){

}
inline void Add(int u){
	vis[u]?del(a[u]):add(a[u]);
	vis[u]^=1;
}
void Mo(int n){
	memset(vis,0,sizeof(vis));
	sort(qr+1,qr+1+n);
	int l=1,r=0;
	for (int i=1;i<=n;++i){
		while (l<qr[i].l)	Add(ver[l++]);
		while (l>qr[i].l)	Add(ver[--l]);
		while (r<qr[i].r)	Add(ver[++r]);
		while (r>qr[i].r)	Add(ver[r--]);
		if (qr[i].lca)	Add(qr[i].lca);
		qr[i].ans=Ans;
		if (qr[i].lca)	Add(qr[i].lca);
	}
}

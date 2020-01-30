/*
	求所有基环树的直径 
	for (int i=1;i<=n;++i){
		if (vis[i])
			continue;
		loop.clear();
		dia=0;
		getLoop(i);
		for (auto i:loop)
			getDia(i.fi,0);
		getMaxDia();
	}
*/
vector<P> e[maxn],loop;
P fa[maxn];
int vis[maxn],islp[maxn];
// 扣环(可处理二元环) 
void getLoop(int u){	
	vis[u]=1;
	for (auto i:e[u]){
		int v=i.fi,w=i.se;
		if (v==fa[u].fi||vis[v]==1)
			continue;
		if (vis[v]){
			loop.pb(mp(v,w));
			islp[v]=1;
			while (v!=u){
				loop.pb(fa[v]);
				v=fa[v].fi;
				islp[v]=1;
			}
		}
		else
			fa[v]=mp(u,w),getLoop(v);
	}
	vis[u]=2;
}
// 求以环上某点为根的子树的直径(不考虑环上的边) 
ll f[maxn],g[maxn],dia;
void getDia(int u,int fa){	
	for (auto i:e[u]){
		int v=i.fi,w=i.se;
		if (v==fa||islp[v])
			continue;
		getDia(v,u);
		if (f[v]+w>=f[u])
			g[u]=f[u],f[u]=f[v]+w;
		else
			g[u]=max(g[u],f[v]+w);
	}
	dia=max(dia,f[u]+g[u]);
}
// 求过环边的最长路径，单调队列优化枚举 
ll sum[maxn<<1];
int q[maxn<<1],h,t;
inline ll value(int pos){
	return -sum[pos]+f[loop[pos].fi];
}
ll getMaxDia(){
	int len=sz(loop);
	for (int i=0;i<len;++i)
		loop.pb(loop[i]);
	sum[0]=loop[0].se;
	for (int i=1;i<sz(loop);++i)
		sum[i]=sum[i-1]+loop[i].se;
	h=t=q[0]=0;
	for (int i=1;i<sz(loop);++i){
		while (h<=t&&i-q[h]>=len) ++h;
		dia=max(dia,sum[i]+f[loop[i].fi]+value(q[h]));
		while (h<=t&&value(i)>=value(q[t])) --t;
		q[++t]=i;
	}
	return dia;
}

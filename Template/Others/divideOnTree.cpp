/*
	mx=INF;
	getrt(1,0,n);
	dfs(rt);
*/
int sz[maxn],vis[maxn],mx,rt;
ll ans;
void getrt(int u,int fa,int sum){	// 获取重心
	sz[u]=1;
	int son=0;
	for (auto v:e[u]){
		if (vis[v]||v==fa)
			continue;
		getrt(v,u,sum);
		sz[u]+=sz[v];
		son=max(son,sz[v]);
	}
	son=max(son,sum-sz[u]);
	if (son<mx)	mx=son,rt=u;
}
void getpath(int u,int fa,...){		// 获取路径
	for (auto v:e[u])	
		if (v!=fa&&!vis[v])	
			getpath(v,u,...);
}
inline ll cal(int u,int val){		// val用于容斥时还原路径
	getpath(u,0,...);				
	ll res=0;
	/*
		do ...						// 根据获取的路径统计答案
	*/
	return res;
}
void dfs(int u){
	vis[u]=1;
	ans+=cal(u,0);
	for (auto v:e[u]){
		if (vis[v])	continue;
		ans-=cal(v,1);				// 容斥扣除非法路径 
		mx=INF;
		getrt(v,u,sz[v]);
		dfs(rt);
	}
}
/*
	非容斥写法,对于子树一边统计一边合并,更通用
*/
int buf[maxn];
vector<int> t;
void getpath(int u,int fa,int w,int ty){
	if (ty==1)	t.pb(w);
	else	buf[w]=0;
	for (int i=head[u];i;i=e[i].ne){
		int v=e[i].v;
		if (vis[v]||fa==v)	continue;
		getpath(v,u,w+1,ty);
	}
}
inline void cal(int u){
	buf[0]++;
	for (int i=head[u];i;i=e[i].ne){
		int v=e[i].v;
		if (vis[v])	continue;
		t.clear();
		getpath(v,u,1,1);
		// 统计
		for (auto j:t)
			if (k>=j)
				ans+=buf[k-j];
		// 合并
		for (auto j:t)
			buf[j]++;
	}
	// 清空
	buf[0]=0;
	for (int i=head[u];i;i=e[i].ne)
		if (!vis[e[i].v])	getpath(e[i].v,u,1,-1);
}
void dfs(int u){
	cal(u);
	vis[u]=1;
	for (int i=head[u];i;i=e[i].ne){
		int v=e[i].v;
		if (vis[v])	continue;
		mx=INF;
		getrt(v,u,sz[v]);
		dfs(rt);
	}
}
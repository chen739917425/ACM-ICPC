int dfn[maxn],s[maxn],top,rt;
vector<int> G[maxn];
void build(int* a,int n){
	sort(a,a+n,[&](int x,int y){return dfn[x]<dfn[y];}); 
	top=0;
	for (int i=0;i<n;++i){
		int u=a[i];
		if (!top){
			s[++top]=u;	
			continue;
		}
		int lca=LCA(u,s[top]);
		// 判断 lca 与 s[top-1]的位置关系 
		while (top>1&&dfn[s[top-1]]>=dfn[lca])	// lca是s[top-1] 或 不在s[top-1]的子树内, s[top-1] -> s[top]
			G[s[top-1]].pb(s[top]),--top;
		// 此时 lca 介于 s[top-1] 与 s[top] 之间 
		if (lca!=s[top])						// 若 lca 不是 s[top], lca -> s[top], s[top] 替换为 lca 
			G[lca].pb(s[top]),s[top]=lca;
		s[++top]=u;
	}
	while (top>1)
		G[s[top-1]].pb(s[top]),--top;
	rt=s[top];
}

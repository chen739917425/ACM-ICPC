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
		// �ж� lca �� s[top-1]��λ�ù�ϵ 
		while (top>1&&dfn[s[top-1]]>=dfn[lca])	// lca��s[top-1] �� ����s[top-1]��������, s[top-1] -> s[top]
			G[s[top-1]].pb(s[top]),--top;
		// ��ʱ lca ���� s[top-1] �� s[top] ֮�� 
		if (lca!=s[top])						// �� lca ���� s[top], lca -> s[top], s[top] �滻Ϊ lca 
			G[lca].pb(s[top]),s[top]=lca;
		s[++top]=u;
	}
	while (top>1)
		G[s[top-1]].pb(s[top]),--top;
	rt=s[top];
}

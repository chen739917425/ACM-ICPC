/*
	g ��ԭͼ
	revg �淴��ͼ
	dom[u] �� u ��֧�����ϵĸ���, ��֧�� u �ĵ����������ĵ�
	����mark(s), sΪ���,��֧�����ĸ� 
	���� u ��·���ϵĵ��Ϊ u ��֧��㣨��ԭͼ�� s �� u �ıؾ��㣩
*/
const int N = 1e6 + 10;
vector<int> revg[N], g[N], buf[N], ord;
int stamp, vis[N], dfn[N], fa[N];
int fs[N], mins[N], dom[N], sem[N], buf2[N];
void dfs(int u) {
	vis[u] = stamp; dfn[u] = sz(ord); ord.pb(u);
	for (auto v : g[u]) if (vis[v] != stamp) fa[v] = u, dfs(v);
}
int find(int u) {
	if (u == fs[u]) return u;
	int v = fs[u];
	fs[u] = find(fs[u]);
	if (~mins[v] && dfn[sem[mins[v]]] < dfn[sem[mins[u]]]) mins[u] = mins[v];
	return fs[u];
}
void mark(int s) {
	ord.clear(); ++stamp; dfs(s);
	for (auto u : ord) fs[u] = u, mins[u] = buf2[u] = -1;
	for (int i=sz(ord)-1;i;--i){
		int u = ord[i], p = fa[u]; sem[u] = p;
		for(auto v : revg[u]) if (vis[v] == stamp){
			if (dfn[v] > dfn[u]) find(v), v = sem[mins[v]];
			if (dfn[v] < dfn[sem[u]]) sem[u] = v;
		}
		buf[sem[u]].pb(u); mins[u] = u; fs[u] = p;
		for (int j=sz(buf[p])-1;j>=0;--j){
			int v = buf[p][j]; find(v);
			if (sem[v] == sem[mins[v]]) dom[v] = sem[v]; else buf2[v] = mins[v];
		}
		buf[p].clear();
	}
	dom[ord[0]] = ord[0];
	for (auto u : ord) if (~buf2[u]) dom[u] = dom[buf2[u]];
}

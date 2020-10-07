//id[i][0] 入树节点的编号, id[i][1] 出树 
// p[i] 是原图点i在线段树上建出的图上对应的点 
int id[N][2], p[N], idx;
vector<P> e[N];
void init(){ 
	for (int i=0;i<=idx;++i) e[i].clear(); 
	idx = 0; 
}
inline void add(int u, int v, int w) {  e[u].pb(mp(v, w)); }
void build(int l, int r, int rt) {
	int m = l + r >> 1;
	id[rt][0] = ++idx, id[rt][1] = ++idx, add(id[rt][0], id[rt][1], 0);
	if (rt>>1) add(id[fa][0], id[rt>>1][0], 0), add(id[rt][1], id[rt>>1][1], 0);
	if (l == r) { p[l] = id[rt][0]; return; }
	build(l, m, rt<<1); build(m+1, r, rt<<1|1);
}
void link(int L, int R, int w, int o, int l, int r, int rt) {
	if (L <= l && R >= r) {
		o?add(id[rt][o], idx, w):add(idx, id[rt][o], w);
		return;
	}
	int m = l + r >> 1;
	if (L <= m) link(L, R, w, o, l, m, rt<<1);
	if (R > m)  link(L, R, w, o, m+1, r, rt<<1|1);
}
// [l1, r1] -> [l2, r2] weight = w 
void link(int l1, int r1, int l2, int r2, int w, int n) { 
	++idx;
	link(l2, r2, 0, 0, 1, n, 1);
	link(l1, r1, w, 1, 1, n, 1);
}

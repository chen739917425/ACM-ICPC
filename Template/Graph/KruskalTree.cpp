struct E{
    int u,v,w;
    bool operator<(const E& t)const{
        return w<t.w;
    }
}edge[maxn];
vector<int> e[maxn<<1];
int fa[maxn<<1],val[maxn<<1],f[maxn<<1][22];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int Kruskal_build(E* edge,int m,int n){
    sort(edge+1,edge+1+m);
    for (int i=1;i<=2*n;++i)  fa[i]=i;
    int id=n;
    for (int i=1;i<=m;++i){
        int x=edge[i].u,y=edge[i].v,w=edge[i].w;
        int fx=find(x),fy=find(y);
        if (fx==fy)  continue;
        fa[fx]=fa[fy]=f[fx][0]=f[fy][0]=++id;
        e[id].pb(fx),e[id].pb(fy);
        val[id]=w;
    }
    return id;
}
// 倍增预处理, 用于对点寻找满足边权限制的最大子树
void dfs(int u){
    for (int i=1;i<=20;++i)
        f[u][i]=f[f[u][i-1]][i-1];
    for (auto v:e[u])
        dfs(v);
}

int root,tot,son[maxn],dfn[maxn],id[maxn],top[maxn],sz[maxn],dep[maxn],f[maxn];
void dfs1(int fa,int u)
{
    f[u]=fa;
    dep[u]=dep[fa]+1;
    sz[u]=1;
    for (int i=head[u];i;i=edge[i].ne)
    {
        int v=edge[i].v;
        if (v==fa)
            continue;
        dfs1(u,v);
        sz[u]+=sz[v];
        if (sz[v]>sz[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int t)
{
    top[u]=t;
    dfn[u]=++tot;
    id[tot]=u;
    if (!son[u])
        return;
    dfs2(son[u],t);
    for (int i=head[u];i;i=edge[i].ne)
    {
        int v=edge[i].v;
        if (v!=f[u]&&v!=son[u])
            dfs2(v,v);
    }
}
int g[maxn],sum[maxn<<2],lazy[maxn<<2];
void build(int l,int r,int rt)
{
    if (l==r)
    {
        sum[rt]=g[id[l]];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void upd(int L,int R,int c,int l,int r,int rt)
{
    sum[rt]+=c*(R-L+1);
    if (L==l&&R==r)
    {
        lazy[rt]+=c;
        return;
    }
    int m=(l+r)>>1;
    if (R<=m)
        upd(L,R,c,l,m,rt<<1);
    else if (L>m)
        upd(L,R,c,m+1,r,rt<<1|1);
    else
        upd(L,m,c,l,m,rt<<1),upd(m+1,R,c,m+1,r,rt<<1|1);
}
int qry(int L,int R,int add,int l,int r,int rt)
{
    if (L==l&&R==r)
        return sum[rt]+add*(R-L+1);
    int m=(l+r)>>1;
    if (R<=m)
        return qry(L,R,add+lazy[rt],l,m,rt<<1);
    else if (L>m)
        return qry(L,R,add+lazy[rt],m+1,r,rt<<1|1);
    else
        return qry(L,m,add+lazy[rt],l,m,rt<<1)+qry(m+1,R,add+lazy[rt],m+1,r,rt<<1|1);
}
void upd_path(int x,int y,int z)
{
    while (top[x]!=top[y]){
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        upd(dfn[top[x]],dfn[x],z,1,tot,1);
        x=f[top[x]];
    }
    if (dfn[x]<dfn[y]) swap(x,y);
    upd(dfn[y],dfn[x],z,1,tot,1);
}
int qry_path(int x,int y)
{
    int res=0;
    while (top[x]!=top[y]){
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        res+=qry(dfn[top[x]],dfn[x],0,1,tot,1);
        x=f[top[x]];
    }
    if (dfn[x]<dfn[y]) swap(x,y);
    res+=qry(dfn[y],dfn[x],0,1,tot,1);
    return res;
}
int main()
{
    int n,m;
    scanf("%d%d%d",&n,&m,&root);
    for (int i=1;i<=n;++i)
        scanf("%d",&g[i]);
    for (int i=0;i<n-1;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs1(0,root);
    dfs2(root,root);
    build(1,tot,1);
    while (m--)
    {
        int op,x,y,z;
        scanf("%d",&op);
        if (op==1) //  路径修改 
        {
            scanf("%d%d%d",&x,&y,&z);
            upd_path(x,y,z);
        }
        else if (op==2) //  路径求和 
        {
            scanf("%d%d",&x,&y);
            printf("%d\n",qry_path(x,y));
        }
        else if (op==3) //  子树修改 
        {
            scanf("%d%d",&x,&z);
            upd(dfn[x],dfn[x]+sz[x]-1,z,1,tot,1);
        }
        else //  子树求和 
        {
            scanf("%d",&x);
            printf("%d\n",qry(dfn[x],dfn[x]+sz[x]-1,0,1,tot,1));
        }
    }
    return 0;
}

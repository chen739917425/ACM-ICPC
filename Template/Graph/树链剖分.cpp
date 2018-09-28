int root,p,tot,son[maxn],id[maxn],rk[maxn],top[maxn],sz[maxn],dep[maxn],f[maxn];
void dfs1(int fa,int u,int deep)
{
    f[u]=fa;
    dep[u]=deep;
    sz[u]=1;
    for (int i=head[u];i;i=edge[i].ne)
    {
        int v=edge[i].v;
        if (v==fa)
            continue;
        dfs1(u,v,deep+1);
        sz[u]+=sz[v];
        if (sz[v]>sz[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int t)
{
    top[u]=t;
    id[u]=++tot;
    rk[tot]=u;
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
        sum[rt]=g[rk[l]];
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
    int fx=top[x],fy=top[y];
    while (fx!=fy)
    {
        if (dep[fx]>dep[fy])
        {
            upd(id[fx],id[x],z,1,tot,1);
            x=f[fx];
        }
        else
        {
            upd(id[fy],id[y],z,1,tot,1);
            y=f[fy];
        }
        fx=top[x],fy=top[y];
    }
    if (id[x]>id[y])
        upd(id[y],id[x],z,1,tot,1);
    else
        upd(id[x],id[y],z,1,tot,1);
}
int qry_path(int x,int y)
{
    int res=0;
    int fx=top[x],fy=top[y];
    while (fx!=fy)
    {
        if (dep[fx]>dep[fy])
        {
            res+=qry(id[fx],id[x],0,1,tot,1);
            x=f[fx];
        }
        else
        {
            res+=qry(id[fy],id[y],0,1,tot,1);
            y=f[fy];
        }
        fx=top[x],fy=top[y];
    }
    if (id[x]>id[y])
        res+=qry(id[y],id[x],0,1,tot,1);
    else 
        res+=qry(id[x],id[y],0,1,tot,1);
    return res;
}
int main()
{
    int n,m;
    scanf("%d%d%d%d",&n,&m,&root,&p);
    for (int i=1;i<=n;++i)
        scanf("%d",&g[i]);
    for (int i=0;i<n-1;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs1(0,root,1);
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
            upd(id[x],id[x]+sz[x]-1,z,1,tot,1);
        }
        else //  子树求和 
        {
            scanf("%d",&x);
            printf("%d\n",qry(id[x],id[x]+sz[x]-1,0,1,tot,1));
        }
    }
    return 0;
}

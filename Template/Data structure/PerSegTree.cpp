//k_th
const int maxn=1e5+10,INF=0x3f3f3f3f;
int cntx,cntn,root[maxn],cnt[maxn*22],ls[maxn*22],rs[maxn*22];
int a[maxn],rk[maxn];
void upd(int pre,int& now,int p,int l,int r)
{
    now=++cntn;
    cnt[now]=cnt[pre]+1;
    ls[now]=ls[pre];
    rs[now]=rs[pre];
    if (l==r)
        return;
    int m=(l+r)>>1;
    if (p<=m)
        upd(ls[pre],ls[now],p,l,m);
    else
        upd(rs[pre],rs[now],p,m+1,r);
}
int qry(int L,int R,int k,int l,int r)
{
    if (l==r)
        return l;
    int c=cnt[ls[R]]-cnt[ls[L]];
    int m=(l+r)>>1;
    if (k<=c)
        return qry(ls[L],ls[R],k,l,m);
    else
        return qry(rs[L],rs[R],k-c,m+1,r);
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        rk[++cntx]=a[i];
    }
    sort(rk+1,rk+1+cntx);
    cntx=unique(rk+1,rk+1+cntx)-rk-1;
    for (int i=1;i<=n;++i)
    {
        int p=lower_bound(rk+1,rk+1+cntx,a[i])-rk;
        upd(root[i-1],root[i],p,1,cntx);
    }
    while (q--)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int ans=qry(root[l-1],root[r],k,1,cntx);
        printf("%d\n",rk[ans]);
    }
    return 0;
}
//  单点修改、单点询问
int cnt,root[maxn],ls[maxn*22],rs[maxn*22];
int a[maxn*22];
void build(int& now,int l,int r)
{
    now=++cnt;
    if (l==r)
    {
        scanf("%d",&a[now]);
        return;
    }
    int m=(l+r)>>1;
    build(ls[now],l,m);
    build(rs[now],m+1,r);
}
void upd(int pre,int& now,int p,int v,int l,int r)
{
    now=++cnt;
    ls[now]=ls[pre];
    rs[now]=rs[pre];
    if (l==r)
    {
        a[now]=v;
        return;
    }
    int m=(l+r)>>1;
    if (p<=m)
        upd(ls[pre],ls[now],p,v,l,m);
    else
        upd(rs[pre],rs[now],p,v,m+1,r);
}
int qry(int p,int l,int r,int now)
{
    if (l==r)
        return a[now];
    int m=(l+r)>>1;
    if (p<=m)
        return qry(p,l,m,ls[now]);
    else
        return qry(p,m+1,r,rs[now]);
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    build(root[0],1,n);
    for (int i=1;i<=q;++i)
    {
        int op,ver,p,v;
        scanf("%d%d%d",&ver,&op,&p);
        if (op==1)
        {
            scanf("%d",&v);
            upd(root[ver],root[i],p,v,1,n);
        }
        else
        {
            root[i]=root[ver];
            printf("%d\n",qry(p,1,n,root[ver]));
        }
    }
    return 0;
}
// 成段修改，区间求和 
const int maxn=1e5+10,INF=0x3f3f3f3f;
int cntn;
int root[maxn],ls[maxn*80],rs[maxn*80];
ll sum[maxn*80],lazy[maxn*80];
void build(int& now,int l,int r)
{
    now=++cntn;
    if (l==r)
    {
        scanf("%lld",&sum[now]);
        return;
    }
    int m=(l+r)>>1;
    build(ls[now],l,m);
    build(rs[now],m+1,r);
    sum[now]=sum[ls[now]]+sum[rs[now]];
}
void upd(int L,int R,int d,int pre,int& now,int l,int r)
{
    now=++cntn;
    ls[now]=ls[pre];
    rs[now]=rs[pre];
    sum[now]=sum[pre]+d*(R-L+1);
    lazy[now]=lazy[pre];
    if (L==l&&r==R)
    {
        lazy[now]+=d;
        return;
    }
    int m=(l+r)>>1;
    if (R<=m)
        upd(L,R,d,ls[pre],ls[now],l,m);
    else if (L>m)
        upd(L,R,d,rs[pre],rs[now],m+1,r);
    else 
        upd(L,m,d,ls[pre],ls[now],l,m),upd(m+1,R,d,rs[pre],rs[now],m+1,r);
    return;
}
ll qry(int L,int R,int add,int l,int r,int now)
{
    if (L==l&&r==R)
        return sum[now]+add*(R-L+1);
    int m=(l+r)>>1;
    if (R<=m)
        return qry(L,R,add+lazy[now],l,m,ls[now]);
    else if (L>m)
        return qry(L,R,add+lazy[now],m+1,r,rs[now]);
    else
        return qry(L,m,add+lazy[now],l,m,ls[now])+qry(m+1,R,add+lazy[now],m+1,r,rs[now]);
}
int main()
{
    int n,m;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        int t=0;
        cntn=0;     
        build(root[0],1,n);
        while (m--)
        {
            char op[2];
            int l,r,_t,d;
            scanf("%s",op);
            if (op[0]=='C')
            {
                scanf("%d%d%d",&l,&r,&d);
                ++t;
                upd(l,r,d,root[t-1],root[t],1,n);
            }
            else if (op[0]=='Q')
            {
                scanf("%d%d",&l,&r);
                printf("%lld\n",qry(l,r,0,1,n,root[t]));
            }
            else if (op[0]=='H')
            {
                scanf("%d%d%d",&l,&r,&_t);
                printf("%lld\n",qry(l,r,0,1,n,root[_t]));
            }
            else
            {
                scanf("%d",&_t);
                t=_t;
            }
        }
    }
    return 0;
}

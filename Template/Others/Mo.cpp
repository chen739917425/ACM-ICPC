//树上莫队
int bs=450,bl[maxn<<1];		
int fa[maxn][25],dep[maxn],st[maxn],ed[maxn],ver[maxn<<1],tim;
int Ans,vis[maxn];
void init(){
	Ans=tim=0;
	for (int i=1;i<2*maxn;++i)
		bl[i]=i/bs+1;
}
void dfs(int u,int f){
	fa[u][0]=f;
	dep[u]=dep[f]+1;
	st[u]=++tim;ver[tim]=u;
	for (int i=1;i<=22;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for (auto v:e[u])
		if (v!=f)	dfs(v,u);
	ed[u]=++tim;ver[tim]=u;
}
inline int Lca(int x,int y){
	if (dep[x]<dep[y])	swap(x,y);
	for (int d=dep[x]-dep[y],i=0;i<=22;++i)
		if ((d>>i)&1)	x=fa[x][i];
	if (x==y)	return x;
	for (int i=22;i>=0;--i)
		if (fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
struct Q{
	int l,r,lca,id,ans;
	void init(int u,int v,int _id){
		id=_id;
		int anc=Lca(u,v);
		if (dep[u]>dep[v])	swap(u,v);
		if (anc==u)	l=st[u],r=st[v],lca=0;
		else	l=ed[u],r=st[v],lca=anc;
	}
	bool operator<(const Q& t)const{
		return bl[l]!=bl[t.l]?bl[l]<bl[t.l]:(bl[l]&1)?r<t.r:r>t.r;
	}
}qr[maxn];

inline void add(int x){

}
inline void del(int x){

}
inline void Add(int u){
	vis[u]?del(a[u]):add(a[u]);
	vis[u]^=1;
}
void Mo(int n){
	memset(vis,0,sizeof(vis));
	sort(qr+1,qr+1+n);
	int l=1,r=0;
	for (int i=1;i<=n;++i){
		while (l<qr[i].l)	Add(ver[l++]);
		while (l>qr[i].l)	Add(ver[--l]);
		while (r<qr[i].r)	Add(ver[++r]);
		while (r>qr[i].r)	Add(ver[r--]);
		if (qr[i].lca)	Add(qr[i].lca);
		qr[i].ans=Ans;
		if (qr[i].lca)	Add(qr[i].lca);
	}
}
//回滚莫队
// 只加不减型
inline void insert(int p,long long &Maxval)
{
    cnt[val[p]]++;
    Maxval = max( Maxval , 1LL * cnt[val[p]] * a[p] );
}
inline void resume(int p)
{
    cnt[val[p]]--;
}
inline void CaptainMo(void)
{
    sort( q+1 , q+m+1 , compare );
    int l = 1 , r = 0 , lastblock = 0;
    for (int i=1;i<=m;i++)
    {
        // 处理同一块中的询问
        if ( belo[q[i].l] == belo[q[i].r] )
        {
            for (int j=q[i].l;j<=q[i].r;j++) cnt_[val[j]]++;
            long long temp = 0;
            for (int j=q[i].l;j<=q[i].r;j++) 
                temp = max( temp , 1LL * cnt_[val[j]] * a[j] );
            for (int j=q[i].l;j<=q[i].r;j++) cnt_[val[j]]--;
            ans[ q[i].id ] = temp; 
            continue; 
        }
        // 如果移动到了一个新的块，就先把左右端点初始化
        if ( lastblock ^ belo[q[i].l] )
        {
            while ( r > R[belo[q[i].l]] ) resume(r--);
            while ( l < R[belo[q[i].l]]+1 ) resume(l++);
            Max = 0 , lastblock = belo[q[i].l];
        }
        // 单调地移动右端点
        while ( r < q[i].r ) insert(++r,Max);
        // 移动左端点回答询问
        long long temp = Max; int  l_ = l;
        while ( l_ > q[i].l ) insert(--l_,temp);
        // 回滚
        while ( l_ < l ) resume(l_++);
        ans[ q[i].id ] = temp;
    }
}
//只减不加型
inline void remove(int p,int &Minval) 
{
    if ( a[p] > n+1 ) return;
    cnt[a[p]]--;
    if ( cnt[a[p]] == 0 ) Minval = min( Minval , a[p] );
}
inline void resume(int p)
{
    if ( a[p] > n+1 ) return;
    cnt[a[p]]++;
}
inline void CaptainMo(void)
{
    sort( q+1 , q+m+1 , compare );
    int l = 1 , r = n , lastblock = 0;
    for (int i=1;i<=m;i++)
    {
        // 处理同一块中的询问
        if ( belo[q[i].l] == belo[q[i].r] )
        {
            for (int j=q[i].l;j<=q[i].r;j++) 
                if ( a[j] <= n+1 ) cnt_[a[j]]++;
            int temp = 0;
            while ( cnt_[temp] ) temp++;
            ans[ q[i].id ] = temp;
            for (int j=q[i].l;j<=q[i].r;j++) 
                if ( a[j] <= n+1 ) cnt_[a[j]]--;
            continue;
        }
        // 如果移动到了一个新的块，就先把左右端点初始化
        if ( belo[q[i].l] ^ lastblock )
        {
            while ( r < n ) resume(++r);
            while ( l < L[belo[q[i].l]] ) remove(l++,ans_);
            Min = ans_ , lastblock = belo[q[i].l];
        }
        // 单调地移动右端点
        while ( r > q[i].r ) remove(r--,Min);
        // 移动左端点回答询问
        int temp = Min , l_ = l;
        while ( l_ < q[i].l ) remove(l_++,temp);
        // 回滚
        while ( l_ > l ) resume(--l_);
        ans[ q[i].id ] = temp;
    }
}
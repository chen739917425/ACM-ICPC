int n;
int id,rt[maxn],fa[maxn*22],sz[maxn*22],ls[maxn*22],rs[maxn*22];
void build(int& now,int l,int r){
    now=++id;
    if (l==r){
        fa[now]=l;
        sz[now]=1;
        return;
    }
    int m=l+r>>1;
    build(ls[now],l,m);
    build(rs[now],m+1,r);
}
void upd(int pre,int& now,int p,int f,int c,int l,int r){
    now=++id;
    ls[now]=ls[pre];
    rs[now]=rs[pre];
    if (l==r){
        fa[now]=f;
        sz[now]=c;
        return;
    }
    int m=l+r>>1;
    if (p<=m) upd(ls[pre],ls[now],p,f,c,l,m);
    else upd(rs[pre],rs[now],p,f,c,m+1,r);
}
int qry(int p,int l,int r,int now){
    if (l==r)
        return now;
    int m=l+r>>1;
    if (p<=m) return qry(p,l,m,ls[now]);
    else return qry(p,m+1,r,rs[now]);
}
int find(int now,int x){
	int pos=qry(x,1,n,now);
	if (fa[pos]==x) return pos;
	return find(now,fa[pos]);
}
void unio(int& now,int x,int y){
	int px=find(now,x),py=find(now,y);
	if (px==py) return;
	if (sz[px]>sz[py]) swap(px,py);
	int fx=fa[px],fy=fa[py],s=sz[px]+sz[py];
	upd(now,now,fx,fy,s,1,n);
	upd(now,now,fy,fy,s,1,n);
}
int main()
{
	int m;
	cin>>n>>m;
	build(rt[0],1,n);
	for (int i=1;i<=m;++i){
		int op;
		scanf("%d",&op);
		if (op==1){
			int x,y;
			scanf("%d%d",&x,&y);
			rt[i]=rt[i-1];
			unio(rt[i],x,y);
		}
		else if (op==2){
			int x;
			scanf("%d",&x);
			rt[i]=rt[x];
		}
		else{
			int x,y;
			scanf("%d%d",&x,&y);
			rt[i]=rt[i-1];
			int px=find(rt[i],x),py=find(rt[i],y);
			printf("%d\n",px==py);
		}
	}
	return 0;
}

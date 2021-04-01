#define ls rt<<1
#define rs rt<<1|1
ll mn[maxn<<2],sec[maxn<<2];	// 叶子处的次值 sec 应设成数据达不到的最值
int xs[maxn<<2],ck[maxn<<2],cnt[maxn<<2][32],lz[maxn<<2];
inline void pushup(int rt){
	if (mn[ls]==mn[rs]){
		mn[rt]=mn[ls];
		sec[rt]=min(sec[ls],sec[rs]);
		ck[rt]=ck[ls]+ck[rs];
	}
	else if (mn[ls]<mn[rs]){
		mn[rt]=mn[ls];
		sec[rt]=min(sec[ls],mn[rs]);
		ck[rt]=ck[ls];
	}
	else{
		mn[rt]=mn[rs];
		sec[rt]=min(mn[ls],sec[rs]);
		ck[rt]=ck[rs];
	}
	xs[rt]=xs[ls]^xs[rs];
	for (int i=0;i<31;++i)	cnt[rt][i]=cnt[ls][i]+cnt[rs][i];
}
inline void dw(int rt,int x){
	if (mn[rt]>=x)	return;
	for (int i=0;i<31;++i)	cnt[rt][i]+=ck[rt]*(((x>>i)&1)-((mn[rt]>>i)&1));
	if (ck[rt]&1)	xs[rt]^=mn[rt]^x;
	mn[rt]=lz[rt]=x;
}
inline void pushdw(int rt){
	if (lz[rt]!=-1){
		dw(ls,lz[rt]);dw(rs,lz[rt]);
		lz[rt]=-1;
	}
}
void build(int l,int r,int rt){
	lz[rt]=-1;
	if (l==r){
		scanf("%d",&xs[rt]);
		mn[rt]=xs[rt];
		sec[rt]=INF;
		ck[rt]=1;
		for (int i=0;i<31;++i)	cnt[rt][i]+=(xs[rt]>>i)&1;
		return;
	}
	int m=l+r>>1;
	build(l,m,ls);
	build(m+1,r,rs);
	pushup(rt);
}
void upd(int L,int R,int x,int l,int r,int rt){
	if (mn[rt]>=x)	return;
	if (L<=l&&r<=R&&sec[rt]>x)	return dw(rt,x);
	pushdw(rt);
	int m=l+r>>1;
	if (L<=m)	upd(L,R,x,l,m,ls);
	if (R>m)	upd(L,R,x,m+1,r,rs);
	pushup(rt);
}
int buf[32];
int qry(int L,int R,int l,int r,int rt){
	if (L<=l&&r<=R){
		for (int i=0;i<31;++i)
			buf[i]+=cnt[rt][i];
		return xs[rt];
	}
	pushdw(rt);
	int m=l+r>>1,res=0;
	if (L<=m)	res^=qry(L,R,l,m,ls);
	if (R>m)	res^=qry(L,R,m+1,r,rs);
	return res;
}
int main()
{
	int n,q;
	cin>>n>>q;
	build(1,n,1);
	int l,r,x,op;
	for (int i=1;i<=q;++i){
		scanf("%d%d%d%d",&op,&l,&r,&x);
		if (op==1)
			upd(l,r,x,1,n,1);
		else{
			int s=qry(l,r,1,n,1)^x,ans=0;
			for (int i=30;i>=0;--i)
				if ((s>>i)&1){
					ans=buf[i]+((x>>i)&1);
					break;
				}
			for (int i=0;i<31;++i)	buf[i]=0;
			printf("%d\n",ans);
		}
	}
	return 0;
}


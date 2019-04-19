//  单点修改,区间询问
inline void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
	if (l==r)
	{
		scanf("%d",&sum[rt]);
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
void update(int p,int x,int l,int r,int rt)
{
	if (l==r)
	{
		sum[rt]+=x;
		return;
	}
	int m=(l+r)>>1;
	if (p<=m)
		update(p,x,lson);
	else 
		update(p,x,rson);
	push_up(rt);
}
int query(int L,int R,int l,int r,int rt)
{
	if (L<=l&&r<=R)
		return sum[rt];
	int m=(l+r)>>1;
	int res=0;
	if (L<=m)
		res+=query(L,R,lson);
	if (R>m)
		res+=query(L,R,rson);
	return res;
}

//  成段修改,区间询问 
void lazy(int rt,int v,int len)
{
	add[rt]+=v;
	sum[rt]+=len*v;
}
void push_up(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void push_dw(int rt,int len)
{
	if (add[rt])
	{
		lazy(rt<<1,add[rt],len-(len>>1));
		lazy(rt<<1|1,add[rt],len>>1);
		add[rt]=0;
	}
}
void build(int l,int r,int rt)
{
	if (l==r)
	{
		scanf("%lld",&sum[rt]);
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
void update(int L,int R,int v,int l,int r,int rt)
{
	if (L<=l&&r<=R)
	{
		lazy(rt,v,r-l+1);
		return;
	}
	push_dw(rt,r-l+1);
	int m=(l+r)>>1;
	if (L<=m)
		update(L,R,v,lson);
	if (R>m)
		update(L,R,v,rson);
	push_up(rt);
}
ll query(int L,int R,int l,int r,int rt)
{
	if (L<=l&&r<=R)
		return sum[rt];
	int m=(l+r)>>1;
	push_dw(rt,r-l+1);
	ll res=0;
	if (L<=m)
		res+=query(L,R,lson);
	if (R>m)
		res+=query(L,R,rson);
	return res;
}

//  扫描线(面积2次、3次交)
inline void push_up(int l,int r,int rt)
{
	if (cnt[rt]>2)
		once[rt]=twice[rt]=more[rt]=d[r+1]-d[l];
	else if (cnt[rt]==2)
	{
		once[rt]=twice[rt]=d[r+1]-d[l];
		if (l==r)
			more[rt]=0;
		else
			more[rt]=once[rt<<1]+once[rt<<1|1];
	}
	else if (cnt[rt]==1)
	{
		once[rt]=d[r+1]-d[l];
		if (l==r)
			twice[rt]=more[rt]=0;
		else
		{
			more[rt]=twice[rt<<1]+twice[rt<<1|1];
			twice[rt]=once[rt<<1]+once[rt<<1|1];
		}
	}
	else
	{
		if (l==r)
			more[rt]=twice[rt]=once[rt]=0;
		else
		{
			once[rt]=once[rt<<1|1]+once[rt<<1];
			twice[rt]=twice[rt<<1]+twice[rt<<1|1];
			more[rt]=more[rt<<1]+more[rt<<1|1];
		}
	}
}			
void update(int L,int R,int v,int l,int r,int rt)
{
	if (L<=l&&r<=R)
	{
		cnt[rt]+=v;
		push_up(l,r,rt);
		return;
	}
	int m=(l+r)>>1;
	if (L<=m)
		update(L,R,v,lson);
	if (R>m)
		update(L,R,v,rson);
	push_up(l,r,rt);
	return;
} 
struct seg
{
	double l,r,y;
	int f;
	seg(){}
	seg(double a,double b,double c,int d):l(a),r(b),y(c),f(d){}
	bool operator < (const seg& a) const
	{
		return y<a.y;
	}
};
seg line[maxn];
update(l,r-1,line[i].f,1,sz,1);
ans+=more[1]*(line[i+1].y-line[i].y); 

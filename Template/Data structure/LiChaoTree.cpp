struct seg{
	int id,vis;
	double k,b;
	double y(int x){return k*x+b;}
};
seg t[maxn<<2],a[maxn];
/*
	insert:
		a[i].id=i,a[i].k=k,a[i].b=b,a[i].vis=1;
		upd(a[i],L,R,1,N,1);
*/ 
void upd(seg s,int l,int r,int rt){
	if (!t[rt].vis){
		t[rt]=s;
		return;
	}
	double l1=t[rt].y(l),r1=t[rt].y(r),l2=s.y(l),r2=s.y(r);
	if (l1>=l2&&r1>=r2)	return;
	if (l1<=l2&&r1<=r2){
		t[rt]=s;
		return;
	}
	int m=l+r>>1;
	double x=(s.b-t[rt].b)/(t[rt].k-s.k);
	if (l1>l2){
		if (x<m)
			upd(t[rt],l,m,rt<<1),t[rt]=s;
		else
			upd(s,m+1,r,rt<<1|1);
	}
	else{
		if (x<m)
			upd(s,l,m,rt<<1);
		else
			upd(t[rt],m+1,r,rt<<1|1),t[rt]=s;
	}
}
void upd(seg s,int L,int R,int l,int r,int rt){
	if (L<=l&&r<=R){
		upd(s,l,r,rt);
		return;
	}
	int m=l+r>>1;
	if (L<=m)	upd(s,L,R,l,m,rt<<1);
	if (R>m)	upd(s,L,R,m+1,r,rt<<1|1);
}
int qry(int x,int l,int r,int rt){
	if (l==r)	return t[rt].id;
	int m=l+r>>1,res=t[rt].id;
	if (x<=m){
		int lid=qry(x,l,m,rt<<1);
		if (a[lid].y(x)>a[res].y(x))	res=lid;
	}
	else{
		int rid=qry(x,m+1,r,rt<<1|1);
		if (a[rid].y(x)>a[res].y(x))	res=rid;
	}
	return res;
}

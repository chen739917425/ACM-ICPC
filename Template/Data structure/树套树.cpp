ull sum[maxn*17*17];
int ls[maxn*17*17],rs[maxn*17*17],rt[maxn],idx;
void upd(int& now,int p,ull x,int l,int r){
	if (!now)	now=++idx;
	sum[now]^=x;
	if (l==r)	return;
	int m=l+r>>1;
	if (p<=m)	upd(ls[now],p,x,l,m);
	else	upd(rs[now],p,x,m+1,r);
}
int qry(vector<int>& L,vector<int>& R,int l,int r){	
	if (l==r){
		ull res=0;
		for (auto i:R)	res^=sum[i];
		for (auto i:L)	res^=sum[i];
		return res?l:-1;
	}
	int m=l+r>>1;
	ull lsum=0;
	for (auto i:R)	lsum^=sum[ls[i]];
	for (auto i:L)	lsum^=sum[ls[i]];
	if (lsum){
		for (int i=0;i<sz(L);++i)	L[i]=ls[L[i]];
		for (int i=0;i<sz(R);++i)	R[i]=ls[R[i]];
		return qry(L,R,l,m);
	}
	for (int i=0;i<sz(L);++i)	L[i]=rs[L[i]];
	for (int i=0;i<sz(R);++i)	R[i]=rs[R[i]];	
	return qry(L,R,m+1,r);
}
void upd(int p,int c){
	for (int i=p;i<=n;i+=i&-i)
		upd(rt[i],c,hs[c],1,M);
}
int qry(int l,int r){
	vector<int> L,R;
	for (int i=r;i;i-=i&-i)
		R.emplace_back(rt[i]);
	for (int i=l;i;i-=i&-i)
		L.emplace_back(rt[i]);
	return qry(L,R,1,M);	
}

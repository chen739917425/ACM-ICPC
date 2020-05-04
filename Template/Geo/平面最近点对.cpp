typedef pair<double,double> P;
inline double dis(P a,P b){
	return sqrt((a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se));
}
P p[maxn],tmp[maxn];
/*	
	sort(p+1,p+1+n)
	solve(1,n);
*/
double solve(int l,int r){
	if (r-l<=3){
		sort(p+l,p+r+1,[&](P a,P b){return a.se<b.se;});
		double d=1e18;
		for (int i=l;i<=r;++i)
			for (int j=i+1;j<=r;++j)
				d=min(d,dis(p[i],p[j]));
		return d;
	}
	int m=l+r>>1;
	double midx=p[m].fi;
	double d=min(solve(l,m),solve(m+1,r));
	for (int i=l,j=m+1,k=0;i<=m||j<=r;){
		if (j>r||(i<=m&&p[i].se<p[j].se))	tmp[k++]=p[i++];
		else tmp[k++]=p[j++];
	}
	for (int i=0;i<r-l+1;++i)
		p[l+i]=tmp[i];
	for (int i=l,j=0;i<=r;++i)
		if (fabs(p[i].fi-midx)<d){
			for (int k=j;k&&p[i].se-tmp[k].se<d;--k)
				d=min(d,dis(p[i],tmp[k]));
			tmp[++j]=p[i];
		}
	return d;
}
/*
	call solve2(n) directly 
*/
double solve2(int n){
	double ans=1e18;
	multiset<P> st;
	sort(p+1,p+1+n,[&](P a,P b){return a.se<b.se;});
	for (int i=1,j=1;i<=n;++i){
		while (j<i&&p[i].se-p[j].se>=ans)
			st.erase(st.find(p[j++]));
		for (auto it=st.upper_bound(mp(p[i].fi-ans,p[i].se));it!=st.end()&&it->fi-p[i].fi<ans;++it)
			ans=min(ans,dis(*it,p[i]));
		st.insert(p[i]);
	}
	return ans;
}

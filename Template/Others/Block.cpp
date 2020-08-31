struct B{
	int bs,bn,n;
	int l[maxn],r[maxn],bl[maxn],cnt[maxn],sum[maxn];
	void init(int _n){
		n=_n;
		bs=sqrt(n);
		bn=n/bs+1;
		for (int i=1;i<=bn;++i)
			sum[i]=l[i]=r[i]=0;
		for (int i=1;i<=n;++i){
			bl[i]=i/bs+1;
			cnt[i]=0;
			if (!l[bl[i]])	l[bl[i]]=i;
			r[bl[i]]=i;
		}
	}
}bk;

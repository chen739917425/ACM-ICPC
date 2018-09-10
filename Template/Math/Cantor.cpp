int fac[20]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int cantor(int* a,int n) //get a's order in permutations
{
	int res=0;
	for (int i=0;i<n;++i)
	{
		int cnt=0;
		for (int j=i+1;j<n;++j)
			if (a[j]<a[i])
				cnt++;
		res+=fac[n-i-1]*cnt;
	}
	return res;
}

void decantor(V& res,int x,int n) //get the x_th permutation 
{
	V v;
	res.clear();
	for (int i=1;i<=n;++i)
		v.push_back(i);
	for (int i=n-1;i>=0;--i)
	{
		int r=x%fac[i],t=x/fac[i];
		x=r;
		sort(v.begin(),v.end());
		res.push_back(v[t]);
		v.erase(v.begin()+t);
	}
	return;
}

// k维空间下n个点的最远 Manhattan 距离 
ll max_Manhattan(ll p[][10],int n,int k)
{
	ll ans=0;
	for (int s=0;s<(1<<k);++s)
	{
		ll mx=-1e18,mn=1e18;
		for (int i=0;i<n;++i)
		{
			ll tmp=0;
			for (int j=0;j<k;++j)
				tmp+=(s&(1<<j))?p[i][j]:-p[i][j];
			mx=max(mx,tmp),mn=min(mn,tmp);
		}
		ans=max(ans,mx-mn);
	}
	return ans;
}

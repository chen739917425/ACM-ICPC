int LCIS(int* a,int* b,int n，int m)
{
	Clear(dp,0);
	for (int i=0;i<n;++i)
	{
		int mx=0;
		for (int j=0;j<m;++j)
		{
			if (a[i]>b[j]&&mx<dp[j])
				mx=dp[j];
			if (a[i]==b[j])
				dp[j]=mx+1;
		}
	}
	return *max_element(dp,dp+m);
}

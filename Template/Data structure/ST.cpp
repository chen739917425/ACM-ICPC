int mn[maxn][32],mx[maxn][32],a[maxn];
void init(int n)
{
	for (int i=1;i<=n;++i)
		mn[i][0]=mx[i][0]=a[i];
	for (int j=1;(1<<j)<=n;++j)
	{
		for (int i=1;i+(1<<j)-1<=n;++i)
		{
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
		}
	}
}
inline int mx_qry(int l,int r)
{
	int k=log(double(r-l+1))/log(2.0);
	return max(mx[l][k],mx[r-(1<<k)+1][k]);
}
inline int mn_qry(int l,int r)
{
	int k=log(double(r-l+1))/log(2.0);
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}

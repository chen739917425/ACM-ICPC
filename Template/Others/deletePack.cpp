int w[maxn],f[maxn],g[maxn][maxn];
void delete_pack(int n,int W)
{
	f[0]=1;
	for (int i=1;i<=n;++i)
		for (int j=W;j>=w[i];--j)
			f[j]+=f[j-w[i]];
	for (int i=1;i<=n;++i)
	{
		g[i][0]=1;
		for (int j=1;j<=W;++j)
			g[i][j]=j<w[i]?f[j]:(f[j]-g[i][j-w[i]]);
	}
}


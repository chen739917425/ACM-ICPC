unsigned long long f[maxn],p[maxn];
void init(char* s, int n)	// use 131 or 13331 to be the base
{
	p[0]=1;
	for (int i=1;i<=n;++i)
	{
		f[i]=f[i-1]*131+(s[i]-'a'+1);
		p[i]=p[i-1]*131;
	}
}
unsigned long long Hash(int l,int r)
{
	return f[r]-f[l-1]*p[r-l+1];
}

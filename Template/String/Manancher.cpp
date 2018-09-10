int r[maxn]; 
int init(char* a,char* b)
{
	int len=strlen(a);
	for (int i=0;i<=len;++i)
	{
		b[2*i+1]='#';
		b[2*i+2]=a[i];
	}
	b[0]='$';
	return 2*len+2;
}
int Manancher(char* s,int n)
{
	int ans=0,p=0;
	r[0]=1;
	for (int i=1;i<n;++i)
	{
		r[i]=p+r[p]>i?min(r[p-(i-p)],p+r[p]-i):1;
		while (s[i-r[i]]==s[i+r[i]])
			++r[i];
		p=i+r[i]>p+r[p]?i:p;
		ans=max(ans,r[i]);
	}
	return ans-1;
}

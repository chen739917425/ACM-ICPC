int ne[maxn];
void init(char *s)
{
	ne[0]=-1;
	int len=strlen(s);
	for (int i=1;i<len;++i)
	{
		int j=ne[i-1];
		while (s[j+1]!=s[i]&&j>=0)
			j=ne[j];
		if (s[j+1]==s[i])
			nt[i]=j+1;
		else
			nt[i]=-1;
	}
}
int match(char* a,char* b)
{
	int n=strlen(a),m=strlen(b),cnt=0;
	while (i<n)
	{
		if (a[i]==b[j])
		{
			++i,++j;
			if (j==m)
			{
				cnt++;
				j=ne[j-1]+1;
			}
		}
		else
		{
			if (j==0)
				++i;
			else
				j=ne[j-1]+1;
		}
	}
	return cnt;
}

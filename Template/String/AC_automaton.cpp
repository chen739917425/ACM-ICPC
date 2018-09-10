struct Trie
{
	static const int N=101010,M=26;
	int ne[N][M],fail[N],fa[N],L,rt,cnt[N];
	void init()
	{
		fail[0]=N-1;
		for (int i=0;i<M;++i)
			ne[N-1][i]=0;
		Clear(cnt,0);
		L=0;
		rt=newnode();
	}
	int newnode()
	{
		for (int i=0;i<M;++i)
			ne[L][i]=0;
		return L++;
	}
	void add(char* s)
	{
		int p=rt;
		for (int i=0;s[i];++i)
		{
			int c=s[i]-'A';
			if (!ne[p][c])
			{
				ne[p][c]=newnode();
				fa[L-1]=p;
			}
			p=ne[p][c];
		}
		cnt[p]++;
	}
	void build()
	{
		V v;
		v.pb(rt);
		for (int i=0;i<v.size();++i)
		{
			int c=v[i];
			for (int j=0;j<M;++j)
			{
				if (ne[c][j])
				{
					v.pb(ne[c][j]);
					fail[ne[c][j]]=ne[fail[c]][j];
				}
				else
					ne[c][j]=ne[fail[c]][j];
			}
		}
	}
	void ac_auto(char* s)
	{
		int p=rt;
		for (int i=0;s[i];++i)
		{
			if (s[i]<'A'||s[i]>'Z')
			{
				p=rt;
				continue;
			}
			int c=s[i]-'A';
			while (!ne[p][c]&&p)
				p=fail[p];
			int tmp=p=ne[p][c];
			while (tmp)
			{
				if (cnt[tmp]!=-1)//if macth,do... 
				{
					
				} 
				tmp=fail[tmp];
			}
		}
	}
}trie;

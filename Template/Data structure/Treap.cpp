struct node
{
	int p,sz,cnt,v,ch[2];
	node(){}
	node(int a,int b):v(a),p(b)
	{
		sz=cnt=1;
		ch[0]=ch[1]=0;
	}
}tp[maxn];
int cnt=0,rt=0;
inline int rand()
{
	static int seed=1007;
	return seed=(int)seed*482711ll%2147483647;
}
inline void upd(int x)
{
	tp[x].sz=tp[x].cnt+tp[tp[x].ch[0]].sz+tp[tp[x].ch[1]].sz;
}
inline void rotate(int& x,int f)
{
	int y=tp[x].ch[f^1];
	tp[x].ch[f^1]=tp[y].ch[f];
	tp[y].ch[f]=x;
	upd(x);
	upd(y);
	x=y;
}
bool find(int x,int v)
{
	if (!x)
		return 0;
	if (tp[x].v==v)
		return 1;
	int son=tp[x].ch[v>tp[x].v];
	if (!son)
		return 0;
	return find(son,v);
}
void insert(int& x,int v)
{
	if (!x)
	{
		tp[x=++cnt]=node(v,rand());
		return;
	}
	if (v==tp[x].v)
	{
		tp[x].cnt++;
		tp[x].sz++;
		return;
	}
	int f=v<tp[x].v;
	insert(tp[x].ch[f^1],v);
	if (tp[tp[x].ch[f^1]].p>tp[x].p)
		rotate(x,f);
	upd(x);
}
void del(int& x,int v)
{
	if (tp[x].v==v)
	{
		if (tp[x].cnt>1)
			tp[x].cnt--;
		else if (!tp[x].ch[0]&&!tp[x].ch[1])
		{
			x=0;
			return;
		}
		else
		{
			int f=tp[tp[x].ch[0]].p>tp[tp[x].ch[1]].p;
			rotate(x,f);
			del(x,v);
		}
	}
	else
		del(tp[x].ch[v>tp[x].v],v);
	upd(x);
}
int k_th(int x,int k)
{
	int ls=tp[x].ch[0],rs=tp[x].ch[1],sz=tp[ls].sz;
	if (sz>=k)
		return k_th(ls,k);
	if (sz+tp[x].cnt>=k)
		return tp[x].v;
	return k_th(rs,k-sz-tp[x].cnt);
}
int count(int x,int v)
{
	if (!x)
		return 0;
	if (v>tp[x].v)
		return tp[x].sz-tp[tp[x].ch[1]].sz+count(tp[x].ch[1],v);
	return count(tp[x].ch[0],v);
}
int pre(int x,int v)
{
	if (!x)
		return -1;
	if (t[x].v==v)
		return v;
	if (t[x].v>v)
		return pre(t[x].ch[0],v);
	return max(pre(t[x].ch[1],v),t[x].v);
}
int suc(int x,int v)
{
	if (!x)
		return -1;
	if (t[x].v==v)
		return v;
	if (t[x].v<v)
		return suc(t[x].ch[1],v);
	return min(suc(t[x].ch[0],v),t[x].v);
}

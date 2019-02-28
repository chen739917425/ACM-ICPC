#define ls t[p].c[0]
#define rs t[p].c[1]
int rt,id;
bool rev[maxn];
struct node
{
	int c[2],f,v,cnt,sz;
}t[maxn];
// operation of splay
inline void pushup(int p)
{
	t[p].sz=t[ls].sz+t[rs].sz+t[p].cnt;
}
inline void pushdw(int p)
{
	if (rev[p])
	{
		swap(ls,rs);
		rev[ls]^=1;
		rev[rs]^=1;
		rev[p]=0;
	}
}
inline void rotate(int x)
{
	int y=t[x].f, z=t[y].f,k=t[y].c[1]==x, w=t[x].c[k^1];
	t[y].c[k]=w, t[w].f=y;
	t[x].c[k^1]=y, t[y].f=x;
	t[z].c[t[z].c[1]==y]=x, t[x].f=z;
	pushup(y),pushup(x);
}
void splay(int x,int g)
{
	while (t[x].f!=g)
	{
		int y=t[x].f,z=t[y].f;
		if (z!=g)
			rotate((t[z].c[1]==y)==(t[y].c[1]==x)? y:x);
		rotate(x);
	}
	if (!g)
		rt=x;
}
// operation of BST
bool find(int x)
{
	if (!rt)
		return 0;
	int p=rt;
	while (t[p].c[x>t[p].v]&&x!=t[p].v)
		p=t[p].c[x>t[p].v];
	splay(p,0);
	return x==t[p].v;
}
void insert(int x)
{
	int p=rt,f=0;
	while (p&&x!=t[p].v)
		f=p,p=t[p].c[x>t[p].v];
	if (p)
		t[p].cnt++;
	else
	{
		p=++id;
		if (f)
			t[f].c[x>t[f].v]=p;
		t[p].f=f;
		ls=rs=0;
		t[p].cnt=t[p].sz=1;
		t[p].v=x;
	}
	splay(p,0);
}
int kth(int k)
{
	int p=rt;
	while (1)
	{
		if (ls&&k<=t[ls].sz)
			p=ls;
		else if (k>t[ls].sz+t[p].cnt)
			k-=t[ls].sz+t[p].cnt,p=rs;
		else
			return p;
	}
}
int rk(int x)
{
	find(x);
	if (t[rt].v<x)
		return t[t[rt].c[0]].sz+t[rt].cnt+1;
	if (t[rt].v>x)
		return 1;
	return t[t[rt].c[0]].sz+1;
}
int pre(int x)
{
	find(x);
	if (t[rt].v<x)
		return rt;
	int p=t[rt].c[0];
	if (p)
		while (rs)
			p=rs;
	return p;
}
int succ(int x)
{
	find(x);
	if (t[rt].v>x)
		return rt;
	int p=t[rt].c[1];
	if (p)
		while (ls)
			p=ls;
	return p;
}
void del(int x)
{
	if (!find(x))
		return;
	if (t[rt].cnt>1)
		t[rt].cnt--,t[rt].sz--;
	else if (!t[rt].c[0])
		t[t[rt].c[1]].f=0,rt=t[rt].c[1];
	else if (!t[rt].c[1])
		t[t[rt].c[0]].f=0,rt=t[rt].c[0];
	else
	{
		int pr=pre(x),suc=succ(x);
		splay(pr,0),splay(suc,pr);
		t[suc].c[0]=0;
		pushup(suc),pushup(pr);
	}
}
// operation of segment
int build(int l,int r,int f)
{
	if (l>r)
		return 0;
	int m=(l+r)>>1;
	int p=++id;
	t[p].v=a[m];
	t[p].f=f;
	t[p].cnt=1;
	ls=build(l,m-1,p);
	rs=build(m+1,r,p);
	pushup(p);
	return p;
}
int find_kth(int k)
{
	int p=rt;
	while (1)
	{
		pushdw(p);
		if (k<=t[ls].sz)
			p=ls;
		else if (k>t[ls].sz+1)
			k-=t[ls].sz+1,p=rs;
		else
			return p;
	}
}
void Reverse(int l,int r)
{
	l=find_kth(l-1),r=find_kth(r+1);
	splay(l,0),splay(r,l);
	rev[t[r].c[0]]^=1;
}

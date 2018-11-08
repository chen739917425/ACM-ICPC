#include<iostream>
#include<algorithm>
#define de(x) cout<<#x<<" = "<<x<<endl
using namespace std;
const int maxn=1e5+10;
struct AVL
{
	int key,h,lc,rc;
}tree[maxn];
int id,root;
inline int newNode(int k,int l,int r)
{
	tree[++id].key=k;
	tree[id].lc=l;
	tree[id].rc=r;
	tree[id].h=0;
	return id;
}
inline int height(int id)
{
	return id ? tree[id].h : 0;
}
inline void upd(int id)
{
	if (!id)
		return;
	int lh=height(tree[id].lc), rh=height(tree[id].rc);
	tree[id].h=max(lh, rh)+1;
}
inline int rightRotate(int id)
{
	int lc=tree[id].lc;
	tree[id].lc=tree[lc].rc;
	tree[lc].rc=id;
	upd(id);
	upd(lc);
	return lc;
}
inline int leftRotate(int id)
{
	int rc=tree[id].rc;
	tree[id].rc=tree[rc].lc;
	tree[rc].lc=id;
	upd(id);
	upd(rc);
	return rc;
}
inline int lrRotate(int id)
{
	tree[id].lc=leftRotate(tree[id].lc);
	return rightRotate(id);
}
inline int rlRotate(int id)
{
	tree[id].rc=rightRotate(tree[id].rc);
	return leftRotate(id);
}
inline int balance(int id)
{
	if (height(tree[id].lc)-height(tree[id].rc) > 1)
	{
		int lc=tree[id].lc;
		if (height(tree[lc].lc) > height(tree[lc].rc))
			return rightRotate(id);
		else
			return lrRotate(id);
	}
	else if (height(tree[id].rc)-height(tree[id].lc) > 1)
	{
		int rc=tree[id].rc;
		if (height(tree[rc].lc) < height(tree[rc].rc))
			return leftRotate(id);
		else
			return rlRotate(id);
	}
	return id;
}
int getMax(int id)
{
	if (!id)
		return 0;
	while (tree[id].rc)
		id=tree[id].rc;
	return id;
}
int getMin(int id)
{
	if (!id)
		return 0;
	while (tree[id].lc)
		id=tree[id].lc;
	return id;
}
void insert(int& rt, int v)
{
	if (!rt)
		rt=newNode(v,0,0);
	else if (v < tree[rt].key)
		insert(tree[rt].lc, v);
	else if (v > tree[rt].key)
		insert(tree[rt].rc, v);
	rt=balance(rt);
	upd(rt);
	return;
}
void del(int& rt, int v)
{
	if (!rt)
		return;
	if (v < tree[rt].key)
		del(tree[rt].lc, v);
	else if (v > tree[rt].key)
		del(tree[rt].rc, v);
	else
	{
		if (tree[rt].lc&&tree[rt].rc)
		{
			if (height(tree[rt].lc) > height(tree[rt].rc))
			{
				int maxId=getMax(tree[rt].lc);
				tree[rt].key=tree[maxId].key;
				del(tree[rt].lc, tree[maxId].key);
			}
			else
			{
				int minId=getMin(tree[rt].rc);
				tree[rt].key=tree[minId].key;
				del(tree[rt].rc, tree[minId].key);
			}
		}
		else
			rt=tree[rt].lc ? tree[rt].lc : tree[rt].rc;
	}
	rt=balance(rt);
	upd(rt);
}
int main()
{

	return 0;
}

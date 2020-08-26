#include<bits/stdc++.h>
#define dd(x) cout<<#x<<" = "<<x<<" "
#define de(x) cout<<#x<<" = "<<x<<endl
#define de_arr(a,s,t) cout<<#a<<": ";for (int z=(s);z<=(t);++z)cout<<a[z]<<" ";cout<<endl;
#define sz(x) int(x.size())
#define All(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
const double eps=1e-8;
inline int sign(double x){return (x>eps)-(x<-eps);}
const int maxn=3e5+10,mod=1e9+7,INF=0x3f3f3f3f;
struct node{
	int ls,rs,sz,val,pr;
}tr[maxn];
int idx,rt;
inline int newnode(int x){
	tr[++idx].val=x;
	tr[idx].pr=rand();
	tr[idx].sz=1;
	tr[idx].ls=tr[idx].rs=0;
	return idx;
}
int stk[maxn],top; 
int build(int* a,int n){	// 以 a[i] 为键值, 对数组 a 建树, 数组 a 下标从 1 开始 
	// O(nlogn)
	for (int i=1;i<=n;++i)
		rt=merge(rt,newnode(a[i]));
	return rt;
	// O(n) 需保证数组 a 已经有序 
	for (int i=1;i<=n;++i){
		int u=newnode(a[i]);
		int t=top;
		while (t&&tr[u].pr<tr[s[t]].pr)	--t;
		if (t)	tr[s[t]].rs=u;
		if (t<top)	tr[u].ls=s[t+1];
		s[++t]=u;
		top=t;
	}
	return s[1];
}
inline void pushup(int u){
	tr[u].sz=tr[tr[u].ls].sz+tr[tr[u].rs].sz+1;
}
void split(int u,int key,int& x,int& y){
	if (!u){
		x=y=0;
		return;
	}
	if (tr[u].val<=key)
		x=u, split(tr[u].rs,key,tr[u].rs,y);
	else
		y=u, split(tr[u].ls,key,x,tr[u].ls);
	pushupd(u);
}
int merge(int x,int y){
	if (!x||!y)	return x+y;
	if (tr[x].pr<=tr[y].tr[y].pr){
		tr[x].rs=merge(tr[x].rs,y);
		pushup(x);
		return x;
	}
	tr[y].ls=merge(x,tr[u].ls);
	pushup(y);
	return y;
}
int main()
{

	return 0;
}


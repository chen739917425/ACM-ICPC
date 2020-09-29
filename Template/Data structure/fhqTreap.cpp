/*	
	如果有向上合并的属性
	若要更新节点的此类属性，需要先将该节点分裂出来，再手动更新所有与此相关的信息，不要遗漏！！
	然后再合并回去
*/
struct node{
	int ls,rs,sz,val,pr;
	int lz;
}tr[maxn];
int idx,rt;
inline int newnode(int x){
	tr[++idx].val=x;
	tr[idx].pr=rand();
	tr[idx].sz=1;
	tr[idx].ls=tr[idx].rs=0;
	return idx;
}
inline void pushup(int u){
	tr[u].sz=tr[tr[u].ls].sz+tr[tr[u].rs].sz+1;
}
inline void pushdw(int u){
	//翻转标记的下传 
	if (tr[u].lz){
		swap(tr[u].ls,tr[u].rs);
		tr[tr[u].ls].lz^=1;
		tr[tr[u].rs].lz^=1;
		tr[u].lz=0;
	}
	//加标记的下传
	if (tr[u].lz){
		if (tr[u].ls){
			tr[tr[u].ls].val+=tr[u].lz;
			tr[tr[u].ls].lz+=tr[u].lz;
		}
		if (tr[u].rs){
			tr[tr[u].rs].val+=tr[u].lz;		
			tr[tr[u].rs].lz+=tr[u].lz;
		}
		tr[u].lz=0;
	}	 
}
//按节点数分裂
void split(int u,int k,int& x,int& y){	
	if (!u){
		x=y=0;
		return;
	}
	pushdw(u);
	if (tr[tr[u].ls].sz+1<=k)
		x=u, split(tr[u].rs,k-tr[tr[u].ls].sz-1,tr[u].rs,y);
	else
		y=u, split(tr[u].ls,k,x,tr[u].ls);
	pushup(u);
}
//按键值分裂
void split(int u,int k,int& x,int& y){	
	if (!u){
		x=y=0;
		return;
	}
	pushdw(u);
	if (tr[u].val<=k)
		x=u, split(tr[u].rs,k,tr[u].rs,y);
	else
		y=u, split(tr[u].ls,k,x,tr[u].ls);
	pushup(u);
}
//合并
int merge(int x,int y){
	if (!x||!y)	return x+y;
	if (tr[x].pr<=tr[y].pr){
		pushdw(x);
		tr[x].rs=merge(tr[x].rs,y);
		pushup(x);
		return x;
	}
	pushdw(y);
	tr[y].ls=merge(x,tr[y].ls);
	pushup(y);
	return y;
}
//对区间 [l, r] 加操作, 区间为数值区间或者序列区间, 取决于 split() 的分裂方法 
inline void upd(int& u,int l,int r,int c){ 
	int x,y,z;
	split(u,r,y,z);
	split(y,l-1,x,y);
	tr[y].val+=c; 
	tr[y].lz+=c;
	u=merge(merge(x,y),z);
}
// 查询最靠右的小于c的数的位置, 其余同类查询类推
int qry(int u,int c){
	int ls=tr[u].ls,rs=tr[u].rs;
	if (tr[rs].mn<c)	return tr[ls].sz+1+qry(rs,c);
	if (tr[u].val<c)	return tr[ls].sz+1;
	if (tr[ls].mn<c)	return qry(ls,c);
	return -1;
}
/*
若树上每个节点代表的是一段区间
可如下封装实现恰好为 k的分裂
所得 x 即 k长度的序列前缀对应的子树 
cnt 为该节点的区间长度
len 为该节点为根的子树的区间长度 
*/
void split(int u,int k,int& x,int& y,int ty){
	if (!u){
		x=0,y=0;
		return;
	}
	if (ty?tr[tr[u].ls].len+tr[u].cnt<=k:tr[tr[u].ls].sz+1<=k)
		x=u,split(tr[u].rs,k-(ty?tr[tr[u].ls].len+tr[u].cnt:tr[tr[u].ls].sz+1),tr[u].rs,y,ty);
	else
		y=u,split(tr[u].ls,k,x,tr[u].ls,ty);
	pushup(u);
}
void Split(int root,int k,int& x,int& y){
	split(root,k,x,y,1);
	if (tr[x].len<k){
		int rest=k-tr[x].len,z;
		split(y,1,y,z,0);
		int t=newnode(tr[y].v,rest);
		tr[y].cnt-=rest;
		tr[y].len-=rest;
		x=merge(x,t);
		y=merge(y,z);
	}
} 
/* 以 a[i] 为键值, 对数组 a 建树, 数组 a 下标从 1 开始 */
inline void ins(int& root,int u){
	int x,y;
	split(root,tr[u].val,x,y);
	root=merge(merge(x,u),y);
}
int build(int* a,int n){	
	idx=0;
	int rt=0;
	for (int i=1;i<=n;++i)
		ins(rt,newnode(a[i]));
	return rt;
}
/* O(n)建树, 需保证数组 a 已经有序 */
int stk[maxn],top; 
void upd(int u){
	if (tr[u].ls)	upd(tr[u].ls);
	if (tr[u].rs)	upd(tr[u].rs);
	pushup(u);
}
void build(int* a,int n){
	idx=top=0;
	for (int i=1;i<=n;++i){
		int u=newnode(a[i]);
		int t=top;
		while (t&&tr[u].pr<tr[stk[t]].pr)	--t;
		if (t)
			tr[stk[t]].rs=u;
		if (t<top)	
			tr[u].ls=stk[t+1];
		stk[++t]=u;
		top=t;
	}
	upd(stk[1]);
	return stk[1];
}

/* 可持久化操作 */
void split(int u,int k,int& x,int& y){
	if (!u){
		x=y=0;
		return;
	}
	if (tr[u].val<=k){
		tr[x=++idx]=tr[u];
		split(tr[x].rs,k,tr[x].rs,y);
		pushup(x);
	}
	else{
		tr[y=++idx]=tr[u];
		split(tr[y].ls,k,x,tr[y].ls);
		pushup(y);
	}
}
int merge(int x,int y){
	if (!x||!y)	return x+y;
	if (tr[x].pr<=tr[y].pr){
		int p=++idx;
		tr[p]=tr[x];
		tr[p].rs=merge(tr[p].rs,y);
		pushup(p);
		return p;
	}
	int p=++idx;
	tr[p]=tr[y];
	tr[p].ls=merge(x,tr[p].ls);
	pushup(p);
	return p;
}
// rt[now]=rt[pre];
// ins(rt[now],c);del(rt[now],c);
// now为当前版本号,pre为当前操作要基于的历史版本号
void ins(int& root,int c){		
	int x,y;
	split(root,c,x,y);
	root=merge(merge(x,newnode(c)),y);
}
void del(int& root,int c){
	int x,y,z;
	split(root,c,y,z);
	split(y,c-1,x,y);
	y=merge(tr[y].ls,tr[y].rs);
	root=merge(merge(x,y),z);
}
/* 平衡树相关操作 */
int Rank(int& root,int c){	// 求c的排名,即比数字c小的数字个数+1
	int x,y;
	split(root,c-1,x,y);
	int rk=tr[x].sz+1;
	root=merge(x,y);
	return rk;
}
int Kth(int u,int k){		// 求排名第k的数字
	if (tr[tr[u].ls].sz+1==k)	return tr[u].val;
	if (k<=tr[tr[u].ls].sz)	return Kth(tr[u].ls,k);
	return Kth(tr[u].rs,k-tr[tr[u].ls].sz-1);
}
int Pre(int& root,int c){	// 求c的前驱
	int x,y;
	split(root,c-1,x,y);
	if (!x)	return -2147483647;
	int ans=Kth(x,tr[x].sz);
	root=merge(x,y);
	return ans;
}
int Suc(int& root,int c){	// 求c的后继
	int x,y;
	split(root,c,x,y);
	if (!y)	return 2147483647;
	int ans=Kth(y,1);
	root=merge(x,y);
	return ans;
}
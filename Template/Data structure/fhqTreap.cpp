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
	//��ת��ǵ��´� 
	if (tr[u].lz){
		swap(tr[u].ls,tr[u].rs);
		tr[tr[u].ls].lz^=1;
		tr[tr[u].rs].lz^=1;
		tr[u].lz=0;
	}
	//�ӱ�ǵ��´�
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
void split(int u,int k,int& x,int& y){
	if (!u){
		x=y=0;
		return;
	}
	pushdw(u);
	if (tr[tr[u].ls].sz+1<=k)	// ���ڵ�������, ������ֵkey������Ϊ tr[u].val <= key 
		x=u, split(tr[u].rs,k-tr[tr[u].ls].sz-1,tr[u].rs,y);
	else
		y=u, split(tr[u].ls,k,x,tr[u].ls);
	pushup(u);
}
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
inline void upd(int& u,int l,int r,int c){ //������ [l, r] �Ӳ���, ����Ϊ��ֵ���������������, ȡ���� split() �ķ��ѷ��� 
	int x,y,z;
	split(u,r,y,z);
	split(y,l-1,x,y);
	tr[y].val+=c; 
	tr[y].lz+=c;
	u=merge(merge(x,y),z);
}
inline void ins(int& root,int u){
	int x,y;
	split(root,tr[u].val,x,y);
	root=merge(merge(x,u),y);
}
int build(int* a,int n){	// �� a[i] Ϊ��ֵ, ������ a ����, ���� a �±�� 1 ��ʼ 
	idx=0;
	int rt;
	for (int i=1;i<=n;++i)
		ins(rt,newnode(a[i]));
	return rt;
}
/*
������ÿ���ڵ�������һ������
�����·�װʵ��ǡ��Ϊ k�ķ���
���� x �� k���ȵ�����ǰ׺��Ӧ������ 
cnt Ϊ�ýڵ�����䳤��
len Ϊ�ýڵ�Ϊ�������������䳤�� 
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

O(n)����, �豣֤���� a �Ѿ����� 
int stk[maxn],top; 
void upd(int u){
	if (tr[u].ls)	upd(tr[u].ls);
	if (tr[u].rs)	upd(tr[u].rs);
	pushup(u);
}
void build(int* a,int n){
	top=0;
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
*/
// �ɳ־û����� 
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

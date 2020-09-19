#define ls tr[x].c[0]
#define rs tr[x].c[1]
struct LCT{
	const static int N=3e5+10;
	struct node{
		int f,c[2],v,s,sz;
	}tr[N];
	int stk[N],r[N],alz[N],mlz[N];	// r为翻转标记, alz为加标记, mlz为乘标记 
	inline void init(int n){	//按需初始化 
		for (int i=1;i<=n;++i){
			tr[i].f=tr[i].c[0]=tr[i].c[1]=r[i]=alz[i]=0;
			tr[i].v=tr[i].s=tr[i].sz=mlz[i]=1;
		}
	}
	inline bool nrt(int x){		// x是否非splay的根 
		return tr[tr[x].f].c[0]==x||tr[tr[x].f].c[1]==x;
	}
	inline void pushup(int x){
		tr[x].sz=tr[ls].sz+tr[rs].sz+1;
		tr[x].s=add(add(tr[ls].s,tr[rs].s),tr[x].v);
	}
	inline void rev(int x){swap(ls,rs);r[x]^=1;}
	inline void A(int x,int c){
		tr[x].v=add(tr[x].v,c);
		tr[x].s=add(tr[x].s,mul(c,tr[x].sz));
		alz[x]=add(alz[x],c);
	}
	inline void M(int x,int c){
		tr[x].v=mul(tr[x].v,c);
		tr[x].s=mul(tr[x].s,c);
		alz[x]=mul(alz[x],c);
		mlz[x]=mul(mlz[x],c);
	}
	inline void pushdown(int x){
		if (mlz[x]!=1){
			if (ls)	M(ls,mlz[x]);
			if (rs)	M(rs,mlz[x]);
			mlz[x]=1;
		}
		if (alz[x]){
			if (ls)	A(ls,alz[x]);
			if (rs)	A(rs,alz[x]);
			alz[x]=0;
		}
		if(r[x]){
			if(ls)	rev(ls);
			if(rs)	rev(rs);
			r[x]=0;
		}
	}
	inline void rotate(int x){
		int y=tr[x].f,z=tr[y].f,k=tr[y].c[1]==x,w=tr[x].c[k^1];
		if(nrt(y))	tr[z].c[tr[z].c[1]==y]=x;
		tr[x].c[k^1]=y;tr[y].c[k]=w;
		if(w)	tr[w].f=y;
		tr[y].f=x;tr[x].f=z;
		pushup(y);
	}
	inline void splay(int x){
		// splay前下放标记 
		int y=x,z=0;
		stk[++z]=y;
		while(nrt(y))	stk[++z]=y=tr[y].f;
		while(z)	pushdown(stk[z--]);
		
		while(nrt(x)){
			y=tr[x].f,z=tr[y].f;
			if(nrt(y))
				rotate((tr[y].c[0]==x)^(tr[z].c[0]==y)?x:y);
			rotate(x);
		}
		pushup(x);
	}
	inline void access(int x){		//使根到 x 的路径在同一 splay 里 
		for(int y=0;x;x=tr[y=x].f)
			splay(x),rs=y,pushup(x);
	}
	inline void makeroot(int x){	//把原树的根换为 x 
		access(x);splay(x);rev(x);
	}
	inline int findroot(int x){		//寻找 x 所在原树的根, 并使其也成为所在splay的根 
		access(x);splay(x);
		while(ls)
			pushdown(x),x=ls;
		splay(x);
		return x;
	}
	inline void split(int x,int y){	//使x到y的路径在同一 splay, 最后x为原树根，y为splay树根 
		makeroot(x);
		access(y);splay(y);
	}
	inline void link(int x,int y){	//连边
		makeroot(x);
		if(findroot(y)!=x)	tr[x].f=y;
	}
	inline void cut(int x,int y){	//删边
		makeroot(x);
		if(findroot(y)==x&&tr[y].f==x&&!tr[y].c[0]){
			tr[y].f=tr[x].c[1]=0;
			pushup(x);
		}
	}
}lct;
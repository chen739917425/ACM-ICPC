struct node{
	int x,y,v,ty,id;
	node(){}
	node(int a,int b,int c,int d=0,int e=0):x(a),y(b),v(c),ty(d),id(e){};
	bool operator < (const node& t) const{
		return x<=t.x;
	}
};
node p[maxn<<2],tmp[maxn<<2];
int fwk[maxn];
inline void upd(int p,int c){
	++p;
	for (int i=p;i<maxn;i+=i&-i)
		fwk[i]+=c;
}
inline int qry(int p){
	++p;
	int res=0;
	for (int i=p;i;i-=i&-i)
		res+=fwk[i];
	return res;
}
void cdq(int l,int r){
	if (l==r)
		return;
	int m=l+r>>1;
	cdq(l,m);cdq(m+1,r);
	int i=l,j=m+1,k=0;
	while (i<=m||j<=r){
		if (j>r||(i<=m&&p[i]<p[j])){
			if (!p[i].ty)
				upd(p[i].y,p[i].v);
			tmp[k++]=p[i++];
		}
		else{
			if (p[j].ty)
				ans[p[j].id]+=qry(p[j].y)*(p[j].ty==2?1:-1);
			tmp[k++]=p[j++];
		}
	}
	for (i=l;i<=m;++i)
		if (!p[i].ty)
			upd(p[i].y,-p[i].v);
	for (i=0;i<k;++i)
		p[l+i]=tmp[i];
}
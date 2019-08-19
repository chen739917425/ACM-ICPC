// 边带权
int fa[maxn],d[maxn]; // d[i]表示i到其父节点的距离 
int add(int a,int b){
	a+=b;
	return (a%k+k)%k; // k为关系环的长度
}
int find(int x){
	if (fa[x]==x)
		return x;
	int rt=find(fa[x]);
	d[x]=add(d[x],d[fa[x]]);
	fa[x]=rt;
	return rt;
}
bool unio(int x,int y,int r){
	int fx=find(x),fy=find(y);
	if (fx==fy)
		return add(d[x],-d[y])==r;
	else{
		d[fx]=add(add(r,d[y]),-d[x]);
		fa[fx]=fy;
		return 1;
	}
}
// 可撤销
stack<int> s;
void unio(int x,int y){
	int fx=find(x),fy=find(y);
	if (fx==fy)	continue;
	if (sz[fx]>sz[fy])
		swap(fx,fy);
	fa[fx]=fy;
	sz[fy]+=sz[fx];
	s.push(fx);
}
void cancel(){
	int fx=s.top();
	s.pop();
	int fy=fa[fx];
	fa[fx]=fx;
	sz[fy]-=sz[fx];
}
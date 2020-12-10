/*
	n 为点数, k 为维度
	下标从 0 开始
	复杂度 O(kn^2/w) - O(kn/w) 
*/ 
const int N=1e4+10,M=sqrt(N)+5,K=10;
struct node{
	int d[K];
}a[N];
bitset<N> s[K][M];
vector<P> v[K];
int id[K][N],n,k,B;
void init(int n,int k){
	for (int j=0;j<k;++j)	v[j].clear();
	for (int i=0;i<n;++i)
		for (int j=0;j<k;++j)
			v[j].pb(mp(a[i].d[j],i));
	for (int j=0;j<k;++j)	sort(All(v[j]));
	for (int i=0;i<n;++i)
		for (int j=0;j<k;++j)
			id[j][lower_bound(All(v[j]),mp(a[i].d[j],i))-v[j].begin()]=i;
	B=sqrt(n);
	for (int j=0;j<k;++j){
		bitset<N> tmp;
		for (int i=0,p=0;i<n;++i){
			tmp.set(id[j][i]);
			if (i==p*B+B-1)	s[j][p++]=tmp;
		}
	}
}
int qry(const node& x){	// 统计不大于或严格小于 x 的点数量 
	bitset<N> ans;
	ans.set();
	for (int j=0;j<k;++j){
		bitset<N> tmp;
		int R=lower_bound(All(v[j]),mp(x.d[j],INF))-v[j].begin()-1;	// 不大于 
		//int R=lower_bound(All(v[j]),mp(x.d[j],-1))-v[j].begin()-1;	// 严格小于 
		if (R>=0){
			int p=R/B,L=p*B;
			if (p-1>=0)	tmp=s[j][p-1];
			for (int i=L;i<=R;++i)	tmp[id[j][i]]=1;
		}
		ans&=tmp;
	}
	return ans.count();
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;++i)
		for (int j=0;j<k;++j)
			scanf("%d",&a[i].d[j]);
	init(n,k);
	for (int i=0;i<n;++i)
		printf("%d\n",qry(a[i])); 
	return 0;
}

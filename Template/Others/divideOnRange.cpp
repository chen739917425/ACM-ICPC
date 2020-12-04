/*
	整体二分
	动态区间第k小
	O(nlogn^2)
*/
int fwk[maxn];
inline void upd(int p,int x){
	for (++p;p<maxn;p+=p&-p)	fwk[p]+=x;
}
inline int qry(int p){
	int res=0;
	for (++p;p;p-=p&-p)	res+=fwk[p];
	return res;
}
struct node{
	int id,x,y,k;
	node(){}
	node(int a,int b,int c,int d=0){id=a,x=b,y=c,k=d;}
};
node q[maxn],lq[maxn],rq[maxn];
int a[maxn],ans[maxn];
void sol(int l,int r,int L,int R){	//[l, r] 为操作序列区间, [L, R] 为值域区间 
	if (L==R){
		for (int i=l;i<=r;++i)
			if (q[i].id>0)	ans[q[i].id]=L;
		return;
	}
	int Mid=L+R>>1;
	int lt=0,rt=0;
	for (int i=l;i<=r;++i){
		if (q[i].id>0){
			int cnt=qry(q[i].y)-qry(q[i].x-1);
			if (cnt>=q[i].k)	lq[++lt]=q[i];
			else{	
				rq[++rt]=q[i];
				rq[rt].k-=cnt;
			}
		}
		else{ 
			if (q[i].y<=Mid)
				upd(q[i].x,q[i].id?-1:1),lq[++lt]=q[i];
			else
				rq[++rt]=q[i];
		}
	}
	for (int i=l;i<=r;++i)
		if (q[i].id<=0&&q[i].y<=Mid)
			upd(q[i].x,q[i].id?1:-1);
	for (int i=1;i<=lt;++i)
		q[l+i-1]=lq[i];
	for (int i=1;i<=rt;++i)
		q[l+lt+i-1]=rq[i];
	if (lt)	sol(l,l+lt-1,L,Mid);
	if (rt)	sol(l+lt,r,Mid+1,R);
}
int main()
{
	int n,m;
	cin>>n>>m;
	int tot=0;
	for (int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		q[++tot]=node(0,i,a[i]);		//插入操作
	}
	char op[2];
	for (int i=1;i<=m;++i){
		ans[i]=-1;
		scanf("%s",op);
		if (op[0]=='Q'){
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			q[++tot]=node(i,l,r,k);		//查询操作
		}
		else{
			int p,x;
			scanf("%d%d",&p,&x);
			q[++tot]=node(-1,p,a[p]);	//删除操作
			q[++tot]=node(0,p,a[p]=x);	//插入操作
		}
	}
	int L=0,R=1e9;	//数值的值域区间
	sol(1,tot,L,R);
	for (int i=1;i<=m;++i)
		if (ans[i]!=-1)	printf("%d\n",ans[i]);
	return 0;
}

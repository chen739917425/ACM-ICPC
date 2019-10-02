const double eps=1e-8;
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	P operator - (const P& t){
		return P(x-t.x,y-t.y);
	}
};
inline int sign(double x){
	return (x>eps)-(x<-eps);
}
inline double cross(P a,P b){
	return a.x*b.y-a.y*b.x;
}
inline double cross(P a,P b,P c){	// ab 叉乘 ac 
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
inline double dis(P a,P b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
// 判断点 q 与凸包 p 的关系, 外:0, 内:1, 边上:-1 
int inConvex(P q,P* p,int n){
	int l=1,r=n-2,pos=-1;
	while (l<=r){
		int m=l+r>>1;
		int s1=sign(cross(p[0],q,p[m])),s2=sign(cross(p[0],q,p[m+1]));
		if (s1<=0&&s2>=0){
			double tmp=sign(cross(p[m],q,p[m+1]));
			return tmp?(tmp<0):-1;
		}
		if (s2<0)
			l=m+1;
		else
			r=m-1;
	}
	return 0;
}
P p[maxn],hull[maxn];
bool cmp(const P& b,const P& c){
	double tmp=cross(b,c,p[0]);
	if (tmp>eps) return 1;
	if (fabs(tmp)<eps&&dis(b,p[0])<dis(c,p[0])) return 1;
	return 0;
}
int graham(P* hull,P* p,int n){		// p 下标从 0 开始, 返回凸包点数, 此时p[0]为凸包左下角的点 
	int k=0;
	for (int i=1;i<n;++i)
		if (sign(p[k].y-p[i].y)>0||(!sign(p[i].y-p[k].y)&&sign(p[k].x-p[i].x)>0))
			k=i;
	swap(p[0],p[k]);
	sort(p+1,p+n,cmp);
	for (int i=0;i<3;++i)
		hull[i]=p[i];
	if (n<3) return n;
	int top=3;
	for (int i=3;i<n;++i){
		while (top>=2&&cross(hull[top-2],hull[top-1],p[i])<eps) --top;
		hull[top++]=p[i];
	}
	return top;
}
// 求多边形面积 
double area(P* p,int n)
{
	double ans=0;
	p[n]=p[0];
	for (int i=0;i<n;++i)
		ans+=cross(p[i],p[i+1]);
	return fabs(ans)/2;
}
// 求多边形边长 
double getlen(P* p,int n)
{
	double ans=0;
	for (int i=0;i<n;++i)
		ans+=dis(p[i],p[i+1]);
	return ans;
}

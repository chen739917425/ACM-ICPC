#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define de(x) cout<<#x<<" = "<<x<<endl
#define dd(x) cout<<#x<<" = "<<x<<" "
using namespace std;
const double eps=1e-8,pi=acos(-1);
const int maxn=1e4+10;
P p[maxn],ch[maxn];
int sign(double x)
{
	return (x>eps)-(x<-eps);
}
struct P
{
	double x,y;
	P(){}
	P(double a,double b):x(a),y(b){}
	bool operator<(const P& c) const
	{
		int f=sign(x-c.x);
		return f?f<0:sign(y-c.y)<0;
	}
	P operator-(const P& c) 
	{
		return P(x-c.x,y-c.y);
	}
};
double norm(P a)
{
	return a.x*a.x+a.y*a.y;
}
double dis(P a,P b)
{
	return sqrt(norm(a-b));
}
double cross(P a,P b)
{
	return a.x*b.y-b.x*a.y;
}
int convexhull(P* p,int n,P* ch)
{
	sort(p,p+n);
	int m=0;
	for (int i=0;i<n;++i)
	{
		while (m>1&&sign(cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]))<=0) --m;
		ch[m++]=p[i];
	}
	int k=m;
	for (int i=n-2;i>=0;--i)
	{
		while (m>k&&sign(cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]))<=0) --m;
		ch[m++]=p[i];
	}
	if (n>1) --m;
	return m;
}
double area(P* p,int n)
{
	double ans=0;
	p[n]=p[0];
	for (int i=0;i<n;++i)
		ans+=cross(p[i],p[i+1]);
	return fabs(ans)/2;
}
double getlen(P* p,int n)
{
	double ans=0;
	for (int i=0;i<n;++i)
		ans+=dis(p[i],p[i+1]);
	return ans;
}

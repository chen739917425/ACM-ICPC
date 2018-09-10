ll exgcd(ll a,ll b,ll& x,ll& y)
{
	if (b==0)
	{
		x=1;
		y=0;
		return a;
	}
	ll r=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return r;
}
bool min_ans(ll a,ll b,ll& x,ll& y,ll n)
{
	ll g=exgcd(a,b,x,y);
	if (n%g)
		return 0;
	x*=n/g;
	y*=n/g;
	ll db=abs(b/g);
	x=((x%db)+db)%db;
	y=(n-a*x)/b;
	return 1;
}

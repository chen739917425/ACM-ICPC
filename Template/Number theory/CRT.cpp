/*
	模数 m[i] 互质时 
	特解 x* = Σa[i]*(M/m[i])*inv(M/m[i], mod m[i])
	通解 x = x* + k*M (k∈Z) 
*/ 
ll exgcd(ll a,ll b,ll& x,ll& y){
	if (b==0){
		x=1,y=0;
		return a;
	}
	ll r=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return r;
}
int a[maxn],m[maxn];
ll crt(int n){
	ll M=1;
	for (int i=0;i<n;++i)
		M*=m[i];
	ll x=0;
	for (int i=0;i<n;++i){
		ll t=M/m[i],inv,y;
		exgcd(t,m[i],inv,y);
		inv=(inv%m[i]+m[i])%m[i];
		x=(x+a[i]*t%M*inv%M)%M;
	}
	return (x%M+M)%M;	// 得到最小非负解 
}

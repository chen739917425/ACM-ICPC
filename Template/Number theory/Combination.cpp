ll fac[maxn],inv[maxn];
void init()
{
	fac[0]=1;
	for (int i=1;i<maxn;++i)
		fac[i]=fac[i-1]*i%mod;
	inv[maxn-1]=kpow(fac[maxn-1],mod-2);
	for (int i=maxn-2;i>=0;--i)
		inv[i]=inv[i+1]*(i+1)%mod;
}
inline ll C(ll n,ll m)
{
	if (m>n)
		return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
ll Lucas(ll n,ll m)
{
	if (m==0)
		return 1;
	return C(n%mod,m%mod)*Lucas(n/mod,m/mod)%mod;
}

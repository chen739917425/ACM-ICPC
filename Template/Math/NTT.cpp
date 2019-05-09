const int G=3,P=1004535809;
int rev[maxn],w[2][maxn];
ll kpow(ll a,ll b)
{
	ll r=1;
	while (b)
	{
		if (b&1) r=r*a%P;
		a=a*a%P;
		b>>=1;
	}
	return r;
}
void init(int n)
{
	int b=0;
	while ((1<<b)<n) ++b;
	w[0][0]=w[1][0]=1;
	for (int i=1,x=kpow(G,(P-1)/n),y=kpow(x,P-2);i<n;++i)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(b-1));
		w[0][i]=ll(x)*w[0][i-1]%P,w[1][i]=ll(y)*w[1][i-1]%P;
	}
}
void ntt(int* a,int n,int f=0)	// f=0 => DFT, f=1 => IDFT
{
	ll c;
	for (int i=0; i<n; i++)
		if (i<rev[i]) 
			swap(a[i],a[rev[i]]);
	for (int l=2;l<=n;l<<=1)
		for (int i=0,t=n/l;i<n;i+=l)
			for (int j=0,k=0,m=l>>1;j<m;++j,k+=t) 
				c=(ll)w[f][k]*a[i+j+m]%P,a[i+j+m]=(a[i+j]-c+P)%P,a[i+j]=(a[i+j]+c)%P;
	if (f) for (int i=0,x=kpow(n,P-2);i<n;++i) a[i]=ll(a[i])*x%P;
}
int a[maxn],b[maxn];
void work()
{
	read(a),read(b);
	init(N);
	ntt(a,N);
	ntt(b,N);
	for (int i=0;i<N;++i)
		a[i]=ll(a[i])*b[i]%P;
	ntt(a,N,1);
}
